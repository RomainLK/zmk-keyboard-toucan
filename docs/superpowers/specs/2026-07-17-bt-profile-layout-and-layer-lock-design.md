# Design — Layout par profil Bluetooth & lock temporaire de layer

**Date** : 2026-07-17
**Clavier** : beekeeb Toucan 36 (Miryoku, ZMK v0.3, `seeeduino_xiao_ble`)
**Branche** : `miryoku`

## Contexte

Le keymap Miryoku du Toucan expose **deux piles de layers complètes** :

- Pile « défaut / Windows » : `U_BASE`=0 … `U_FUN`=9
- Pile « Mac » : `U_MBASE`=10 … `U_MFUN`=17

Le passage Win↔Mac se fait **manuellement** via `&to U_BASE` / `&to U_MBASE`
(behaviors `u_to_U_BASE` / `u_to_U_MBASE`, définis dans `miryoku_double_tap_guard.dtsi`
comme `MIRYOKU_DOUBLE_TAP_GUARD(u_to_U_##LAYER, &to U_##LAYER)`).

La sélection de profil BT se fait via `&bt BT_SEL 0..4` (layer Media / MMedia).

Ce document couvre **deux features indépendantes**. Chacune aura son propre plan
d'implémentation.

---

## Feature 1 — Layout mémorisé par profil Bluetooth (automatique, persisté)

### Objectif

Quand on bascule (ou reconnecte automatiquement) sur un profil Bluetooth, le clavier
restaure **tout seul** le layout (Win ou Mac) qui était actif la dernière fois sur ce
profil. Exemple : le profil du Mac reste sur le layout Mac quand on y revient, même après
une reconnexion automatique au réveil (sans appui touche).

L'association est **dynamique / apprise** : le clavier retient, pour chaque profil, le
dernier layout choisi manuellement par l'utilisateur, et le persiste en flash.

### Architecture

Un **module ZMK custom en C** : `RomainLK/zmk-toucan-behaviors`, référencé dans
`config/west.yml` (même pattern que les modules existants `cirque-input-module`,
`zmk-tri-state`, `zmk-rgbled-widget`).

Le module s'abonne à deux évènements ZMK :

1. **`ble_active_profile_changed`** (`zmk/events/ble_active_profile_changed.h`)
   → déclenché quand le profil BLE actif change (sélection ou reconnexion).
   Handler : lit l'index du profil actif (`zmk_ble_active_profile_index()`), lit le
   layout mémorisé pour cet index, et applique `zmk_keymap_layer_to(layer)` avec
   `layer` ∈ {`U_BASE`=0, `U_MBASE`=10}. `zmk_keymap_layer_to` reproduit exactement le
   comportement de `&to`.

2. **`layer_state_changed`** (`zmk/events/layer_state_changed.h`)
   → déclenché à chaque changement d'état de layer.
   Handler : calcule `mac = zmk_keymap_layer_active(U_MBASE)` (booléen stable — voir
   note ci-dessous), récupère l'index du profil actif, et si `mac` diffère de la valeur
   stockée pour ce profil → met à jour le tableau + sauve dans les settings.

> **Note « booléen Mac stable »** : `U_MBASE`=10 sépare les deux piles. Les layers
> momentanés Mac (MNav=13 … MFun=17) sont tous > 10, les Win (Nav=4 … Fun=9) tous < 10.
> Donc `zmk_keymap_layer_active(U_MBASE)` reste vrai sur toute la pile Mac et faux sur
> toute la pile Win, quel que soit le layer momentané tenu. C'est un encodage fiable de
> « Mac vs Win ».

### Persistance

Subsystem `settings` de Zephyr (NVS / flash), tel qu'utilisé par ZMK lui-même.

- Clé : `toucan/pl` (namespace court).
- Valeur : tableau de `ZMK_BLE_PROFILE_COUNT` octets (défaut 5), 1 octet par profil,
  contenant l'index de base layer mémorisé (`0` = Win, `10` = Mac).
- Chargement au boot ; sauvegarde uniquement quand une valeur change réellement.

### Flux de données

```
Boot
  └─ settings_load → tableau[profil] (défaut : tout 0/Win)
  └─ appliquer le layout du profil actif courant

Utilisateur switch Win↔Mac (touches existantes u_to_U_BASE / u_to_U_MBASE)
  └─ &to fait zmk_keymap_layer_to(0|10)
       └─ layer_state_changed → mac = active(U_MBASE)
            └─ si tableau[profil_actif] != mac → tableau[profil_actif] = mac ; settings_save

Changement / reconnexion de profil BT
  └─ ble_active_profile_changed
       └─ layer = tableau[nouveau_profil]
            └─ zmk_keymap_layer_to(layer)
```

### Décisions & garanties

- **Zéro modification du keymap.** La détection se branche sur les touches de switch
  existantes (`u_to_U_BASE` / `u_to_U_MBASE`) via l'évènement `layer_state_changed`.
  Feature 1 = uniquement le module C + son wiring `west.yml`.
- **Anti-boucle.** La restauration (`ble_active_profile_changed` → `zmk_keymap_layer_to`)
  déclenche un `layer_state_changed`, mais le handler écrit alors la **même** valeur →
  pas d'écriture flash, pas de boucle infinie. Idempotent.
- **Usure flash.** Écriture uniquement sur changement réel de préférence (échelle
  humaine, quelques fois par jour au plus) → négligeable.
- **Constantes de layer.** `U_BASE`=0 et `U_MBASE`=10 sont dupliqués côté module (via
  Kconfig `CONFIG_TOUCAN_*` ou constantes commentées), avec un commentaire renvoyant à
  `config/miryoku/custom_config.h` comme source de vérité. À garder synchronisés si les
  index changent.

### Cas limites / gestion d'erreur

| Situation | Comportement |
|---|---|
| Settings pas encore chargés / lecture échouée | Défaut : Win (0) pour tous les profils |
| Valeur stockée invalide (ni 0 ni 10) | Traitée comme Win (0) |
| Pas de profil BLE actif (USB pur depuis le boot) | Défaut Win ; l'enregistrement se fait sur l'index de profil courant retourné par l'API |
| Nombre de profils | Tableau dimensionné sur `ZMK_BLE_PROFILE_COUNT` |

### Vérification

Firmware embarqué → pas de tests unitaires classiques. Validation par build + flash +
tests manuels :

1. Switcher manuellement Mac sur profil 0, Win sur profil 1.
2. Basculer profil 0 → 1 → 0 : vérifier que le layout suit automatiquement.
3. Éteindre / rallumer le clavier : vérifier que les associations persistent.
4. Laisser le clavier se rendormir puis se reconnecter au réveil sur un profil : vérifier
   que le layout est restauré sans appui touche.

---

## Feature 2 — Toggle-lock de layer (Nav, Num, Mouse + variantes Mac)

### Objectif

Verrouiller un layer momentané « à la demande » pour ne plus avoir à tenir le pouce, et
le déverrouiller en re-tapant la même touche. Layers concernés : **Nav, Num, Mouse** et
leurs variantes Mac (**MNav, MNum, MMouse**).

### Architecture

**100% ZMK natif, zéro code C.** On utilise le behavior `&tog LAYER` (toggle layer).

Sur chaque layer verrouillable, on ajoute une touche `&tog` pointant vers **lui-même** :

| Layer | Touche à ajouter |
|---|---|
| `U_NAV` | `&tog U_NAV` |
| `U_NUM` | `&tog U_NUM` |
| `U_MOUSE` | `&tog U_MOUSE` |
| `U_MNAV` | `&tog U_MNAV` |
| `U_MNUM` | `&tog U_MNUM` |
| `U_MMOUSE` | `&tog U_MMOUSE` |

### Flux d'usage

1. Tenir le pouce d'activation (ex : Space → Nav actif momentanément).
2. Taper la touche `&tog U_NAV` d'un doigt libre → Nav est togglé ON.
3. Lâcher le pouce → Nav reste actif (le toggle est indépendant du hold-tap).
4. La touche lock est toujours accessible (Nav actif) → la re-taper déverrouille et
   revient à la base.

### Placement

Chaque layer cible possède des slots `U_NA` libres (vérifié dans `custom_config.h`).
La touche lock sera placée à une position **stable et côté main opposée** au pouce
d'activation (pour pouvoir la taper avant de lâcher le pouce). Position exacte finalisée
au plan d'implémentation. Candidats identifiés :

- `U_NAV` / `U_MNAV` : slot `U_NA` pinky haut-gauche (activé par le pouce gauche → main
  gauche libre).
- `U_NUM` / `U_MNUM` : Num est activé par le pouce droit (RET), chiffres à gauche → viser
  un slot `U_NA` accessible.
- `U_MOUSE` / `U_MMOUSE` : Mouse activé par le pouce gauche (TAB), déplacements à droite.

### Détail — layer Win `MOUSE` non custom

`U_NAV`, `U_NUM` et toutes les variantes Mac sont déjà redéfinis dans
`custom_config.h`. En revanche le layer **Win `MOUSE` n'y est pas** : il vient du défaut
Miryoku babel. Pour y ajouter la touche lock, il faudra **redéfinir
`MIRYOKU_LAYER_MOUSE`** dans `custom_config.h` (copie du défaut + insertion du `&tog`).

### Interaction `&tog` × système de base `&to`

Un changement de base (`u_to_U_BASE` / `u_to_U_MBASE` = `&to`) désactive tous les layers
togglés → un layer verrouillé se libère proprement si on change de layout. Comportement
voulu (pas de layer fantôme qui traîne après un switch Win↔Mac).

### Vérification

Build + flash + test manuel :

1. Tenir Space (Nav), taper la touche lock, lâcher Space → vérifier que Nav reste actif.
2. Re-taper la touche lock → vérifier retour à la base.
3. Répéter pour Num et Mouse, côté Win et côté Mac.
4. Verrouiller Nav puis changer de base (Win↔Mac) → vérifier que le lock se libère.

---

## Portée & séquencement

Les deux features sont indépendantes et peuvent être implémentées séparément :

- **Feature 2** (toggle-lock) : petite, sans risque, sans code C. Bon premier morceau.
- **Feature 1** (layout par profil) : nouveau repo module + code C + persistance settings.
  Plus lourde, validée surtout par test HW.

Chaque feature suivra son propre cycle spec → plan → implémentation.
