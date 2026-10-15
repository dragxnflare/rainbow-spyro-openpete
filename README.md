# Rainbow Spyro 🌈🐉

**Animated RGB shader for the original Spyro the Dragon (1998) via OpenPete.**

**Creator:** [dragxnflare](https://www.twitch.tv/dragxnflare)  
**Development assistance:** ChatGPT (OpenAI)  
**Release:** v0.1.0  
**Supported game:** OpenPete Spyro 1; developed for the OpenPete v0.4.2 mod API.

Rainbow Spyro makes rainbow color bands flow smoothly across Spyro's rendered model. It is a **cosmetic-only** mod: no new abilities, speed boosts, cheats, altered levels, or gameplay rules. The animation is a fragment shader controlled by OpenPete's mod SDK.

## Features

- Flowing animated rainbow / RGB colors on Spyro
- Separate adjustable speed, color-band density, and rainbow strength
- Leaves level geometry and the HUD unaffected by selecting OpenPete's player material channel
- Original, human-readable C and GLSL source included
- No ripped PlayStation assets or game files included

## Requirements

- A working installation of **OpenPete's PC port of Spyro the Dragon (1998)**, with its modding support and SDK.
- Your own original game data, as required by OpenPete. This ZIP contains no game files.

## Installation (Windows)

1. Close OpenPete.
2. Download **`rainbow-spyro-v0.1.0.zip`** from the GitHub Release's **Assets** section. (Do **not** use GitHub's automatic **Source code (zip)** download as the installation file.)
3. Put the ZIP, **without extracting it**, into the `mods` directory beside `openpete-spyro1.exe` (for example `C:\openpete\mods\`).
4. Start `openpete-spyro1.exe` and enter a level.
5. Press **M**, open **Mods**, and check that **Rainbow Spyro (Animated RGB)** is enabled.
6. If you already have a `mods/enabled.txt`, ensure it contains `rainbow-spyro` on its own line. Otherwise OpenPete discovers all mods by default.

**Already using the mod?** To update it, close the game, remove any older Rainbow Spyro ZIP or extracted `mods/rainbow-spyro` folder, and install this ZIP. OpenPete prioritizes an extracted mod folder over a ZIP of the same mod ID.

## Change the rainbow

Press **M → Mods → Rainbow Spyro** to edit the following settings. Click **Apply** (if shown) to save and reload the mod.

| Setting | Default | Function |
|---|---:|---|
| Rainbow speed | `0.18` | Color cycles per second; `0` pauses the animation |
| Rainbow stripe density | `0.0035` | More or fewer visible bands |
| Rainbow strength | `0.95` | Blend with Spyro's original colors (`0` = original, `1` = full rainbow) |

**How it looks:** The wave pattern is based on screen coordinates rather than Spyro's texture UVs, so bands sweep across the on-screen silhouette and are not locked to individual body parts. The effect can also color his horns and other details rendered with the same player channel.

## Troubleshooting

- **Not listed in Mods?** Verify the archive includes `mod.toml` at its top level and is in the correct `mods` directory. The mod ID is `rainbow-spyro`.
- **Listed but not loading?** Check the game's mod log and `.build/` compile logs for C or shader errors. The SDK is needed by OpenPete for local compilation.
- **Conflict with another player shader?** Temporarily disable other mods that apply shaders to the player channel.
- **Want to customize the source?** Extract the ZIP into `mods/rainbow-spyro/`, delete or move the original ZIP, edit the shader in `shaders/rainbow.frag` or settings in `mod.toml`, then relaunch.

This is the author's first public release candidate. The uploader reports the core rainbow effect working while streaming. Additional OpenPete versions and hardware configurations have not been independently verified.

## Source / credits / rights

The source is included in the ZIP under `src/` and `shaders/`. The design, public release, and playtesting are credited to **dragxnflare**, with mod code and documentation developed in collaboration with **OpenAI ChatGPT**.

See [`LICENSE`](LICENSE) for permissions. All Spyro, Insomniac Games, Sony, and other marks are the property of their respective rights holders. This is an unofficial, unaffiliated fan-made modification.

### OpenPete documentation

- [Getting started](https://openpete.com/docs/modding/getting-started/)
- [Shaders](https://openpete.com/docs/modding/shaders/)
- [Publishing](https://openpete.com/docs/modding/publishing/)
