# Feature 2 — Toggle Layer-Lock via Combos — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a "lock the current momentary layer" gesture to Nav and Num (Win + Mac), so the thumb can be released, and re-pressing the same gesture unlocks.

**Architecture:** Pure ZMK devicetree — four layer-restricted combos, each firing the native `&tog <layer>` (toggle-layer) behaviour. No C code, no keymap binding changes. Combos live in the existing, already-included `config/miryoku/custom_combo.dtsi`.

**Tech Stack:** ZMK v0.3, Zephyr devicetree, `zmk-helpers` `ZMK_COMBO` macro, `zmk,behavior-toggle-layer` (`&tog`).

## Global Constraints

- Board: `seeeduino_xiao_ble`; shields per `build.yaml` (`toucan_left rgbled_adapter nice_view_gem`, `toucan_right rgbled_adapter`).
- ZMK pinned to `v0.3` (see `config/west.yml`).
- Combos MUST be **layer-restricted** to their target layer — never active on the base layer.
- **No changes to any layer's `bindings`** in `custom_config.h`. This feature only adds combos.
- Reuse the repo's `ZMK_COMBO(name, bindings, keypos, layers, timeout, idle)` macro (from `zmk-helpers/helper.h`); do not hand-write raw `combos {}` nodes.
- Position labels come from `zmk-helpers/key-labels/42.h` (already included at `miryoku.dtsi:19`). On this 36-key board the index-column keys are label index `0`: **B=`LT0`, G=`LM0`, J=`RT0`, M=`RM0`** (verified against `mapping/42/corne.h`).
- Layer index macros (`U_NUM`=7, `U_MNUM`=16, `U_NAV`=4, `U_MNAV`=13) come from `config/miryoku/custom_config.h`, included before `custom_combo.dtsi`.

## Testing note (TDD adaptation)

A devicetree keymap has no unit-test harness. The two real verification gates are:
1. **The firmware compiles** (CI build green, or local `west build`).
2. **On-hardware behaviour** matches the expected-behaviour checklist below.

This plan defines those expected behaviours up front (Step 5), then implements and verifies against them — the same discipline as TDD, adapted to firmware.

## File Structure

- **Modify only:** `config/miryoku/custom_combo.dtsi` — append four `ZMK_COMBO(...)` lines after the existing `space_tab_*` combos.

No other file changes. `custom_combo.dtsi` is already `#include`d at `config/miryoku/miryoku.dtsi:351`, after all behaviour definitions and after `&tog` (from `<behaviors.dtsi>`), so the new combos compile in place.

---

### Task 1: Add the four layer-lock combos

**Files:**
- Modify: `config/miryoku/custom_combo.dtsi` (append after the `space_tab_mac` line)

**Interfaces:**
- Consumes: `ZMK_COMBO` macro (`zmk-helpers/helper.h`); position labels `LT0 LM0 RT0 RM0` (`key-labels/42.h`); layer macros `U_NUM U_MNUM U_NAV U_MNAV` (`custom_config.h`); `&tog` (`<behaviors.dtsi>`).
- Produces: four combo nodes `combo_num_lock_win`, `combo_num_lock_mac`, `combo_nav_lock_win`, `combo_nav_lock_mac`. Nothing else in the codebase references these — this is a leaf change.

- [ ] **Step 1: Read the current end of the file to confirm the insertion anchor**

Run: `cat config/miryoku/custom_combo.dtsi`
Expected: the last two active lines are
```c
ZMK_COMBO(space_tab_win, &kp SPACE, LH1 LH0, U_BASE)
ZMK_COMBO(space_tab_mac, &kp SPACE, LH1 LH0, U_MBASE)
```

- [ ] **Step 2: Append the four combos**

Add these lines at the end of `config/miryoku/custom_combo.dtsi`, after the `space_tab_mac` line:

```c

// ── Layer-lock combos (Feature 2) ───────────────────────────────────────────
// Press the combo while holding the layer thumb → &tog locks the layer, so the
// thumb can be released. The combo stays reachable (target layer still active)
// → press it again to unlock and return to base.
//
// Convention: the two index-column keys (top + home) on the hand OPPOSITE the
// activating thumb, restricted to the target layer:
//   Num  (right thumb / RET)   → B + G = LT0 LM0   (left index column)
//   Nav  (left thumb / SPACE)  → J + M = RT0 RM0   (right index column)
//
// require-prior-idle-ms = 150 stops the combo from firing mid-typing-stream —
// notably "+=" on the Num layer, where LT0/LM0 are PLUS/EQUAL. timeout = 50
// matches the repo's COMBO_TERM.
ZMK_COMBO(num_lock_win, &tog U_NUM,  LT0 LM0, U_NUM,  50, 150)
ZMK_COMBO(num_lock_mac, &tog U_MNUM, LT0 LM0, U_MNUM, 50, 150)
ZMK_COMBO(nav_lock_win, &tog U_NAV,  RT0 RM0, U_NAV,  50, 150)
ZMK_COMBO(nav_lock_mac, &tog U_MNAV, RT0 RM0, U_MNAV, 50, 150)
```

- [ ] **Step 3: Verify it compiles (CI build gate)**

The reliable build for this repo is GitHub Actions (`.github/workflows/build.yml` → `zmkfirmware/zmk` reusable workflow). Commit on the current `miryoku` branch (Step 4), push, then:

Run: `gh run watch --exit-status $(gh run list --branch miryoku --limit 1 --json databaseId --jq '.[0].databaseId')`
Expected: the run finishes **green**. A devicetree syntax error or an unknown label/behaviour would fail the `toucan_left`/`toucan_right` matrix jobs.

(Optional local alternative, only if a ZMK/Zephyr west workspace is already set up:
`west build -p -b seeeduino_xiao_ble -- -DSHIELD="toucan_left rgbled_adapter nice_view_gem" -DZMK_CONFIG="$(pwd)/config"` — Expected: build succeeds, `zmk.uf2` produced.)

- [ ] **Step 4: Commit**

```bash
git add config/miryoku/custom_combo.dtsi
git commit -m "feat(keymap): add toggle layer-lock combos for Nav and Num

B+G (LT0 LM0) locks Num, J+M (RT0 RM0) locks Nav, each restricted to its
own layer (Win + Mac). require-prior-idle-ms guards against accidental
firing during typing (e.g. += on Num).

Co-Authored-By: Claude Opus 4.8 (1M context) <noreply@anthropic.com>"
```

(Push before/with Step 3 so CI runs: `git push -u origin miryoku`.)

- [ ] **Step 5: Flash and verify on hardware (behaviour gate — user-performed)**

Flash the new firmware to **both halves** (combos are collected centrally, both firmwares must match): download the `toucan_left...` and `toucan_right...` UF2 artifacts from the green CI run and drag each onto the matching XIAO in bootloader mode.

Then walk the expected-behaviour checklist:

- [ ] **Nav lock (Win):** on the Win base, hold left thumb (SPACE → Nav), press **J+M** together, release the thumb → Nav stays active (arrows/nav keys work without holding).
- [ ] **Nav unlock:** press **J+M** again → returns to base (letters type normally).
- [ ] **Num lock (Win):** hold right thumb (RET → Num), press **B+G** together, release the thumb → Num stays active (digits work without holding). Press **B+G** again → unlocks.
- [ ] **Mac variants:** switch to Mac base (`u_to_U_MBASE`), repeat the Nav and Num lock/unlock checks → they toggle the Mac layers (MNav/MNum), not the Win ones.
- [ ] **No accidental fire while typing:** on the Num layer, type `+=` and a few number rows at normal speed → the layer does **not** lock. If it does, raise `require-prior-idle-ms` (e.g. to 200) on the `num_lock_*` combos and re-flash.
- [ ] **Lock releases on base switch:** lock Nav, then press a base switch (`u_to_U_BASE` / `u_to_U_MBASE`) → the lock clears (no stale Nav layer). This is the expected `&tog` × `&to` interaction.

If a behaviour check fails, fix inline (positions, layer restriction, or idle timing) and re-run Steps 3–5.

---

## Self-Review

**Spec coverage** (against `docs/superpowers/specs/2026-07-17-...-design.md`, Feature 2):
- Objective (lock Nav/Num, thumb-free, re-press to unlock) → Task 1, Steps 2 & 5. ✓
- 4 combos table (positions, layer restriction, binding) → Step 2 code matches the spec table (`LT0 LM0`/`RT0 RM0`, `U_NUM`/`U_MNUM`/`U_NAV`/`U_MNAV`, `&tog ...`). ✓
- Layer-restriction-mandatory note → Global Constraints + Step 2 comment. ✓
- Timeout/`require-prior-idle` note → Step 2 (50/150) + Step 5 tuning check. ✓
- No layer-binding changes → Global Constraints; only `custom_combo.dtsi` touched. ✓
- `&tog` × `&to` interaction → Step 5 last check. ✓
- Verification steps (Nav/Num, Win/Mac, base-switch release) → Step 5 checklist. ✓

**Placeholder scan:** No TBD/TODO; exact code, exact file, exact commands present. ✓

**Type/name consistency:** Combo names, position labels, layer macros, and `&tog` targets are identical between the Global Constraints, Step 2 code, and the spec table. ✓
