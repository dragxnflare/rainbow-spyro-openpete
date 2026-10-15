#include <openpete_mod_api.h>

// Visual effect only; no game RAM or gameplay logic changes.
static const openpete_mod_api_t *g_api;
static openpete_mod_t *g_self;
static int g_material = -1;
static float g_speed;
static float g_band_density;
static float g_strength;

// Called at every rendered presentation moment (including interpolated frames).
static void rainbow_present(const openpete_present_ctx_t *ctx) {
    // Spyro simulation is 29.913 ticks/s. Include interpolation alpha for
    // smooth movement even when OpenPete renders at 60+ FPS.
    double cycles = ((double)ctx->tick + (double)ctx->alpha)
                  * (double)g_speed / 29.913;
    double whole = (double)(unsigned long long)cycles;
    float phase = (float)(cycles - whole);
    float params[4] = { phase, g_band_density, g_strength, 0.0f };
    g_api->material_set_params(g_self, g_material, params, sizeof(params));
}

int openpete_mod_entry(const openpete_mod_api_t *api, openpete_mod_t *self) {
    g_api = api;
    g_self = self;

    g_speed        = (float)api->config_float(self, "speed", 0.18);
    g_band_density = (float)api->config_float(self, "band_density", 0.0035);
    g_strength     = (float)api->config_float(self, "strength", 0.95);

    int shader = api->shader_register(self, "shaders/rainbow.frag");
    if (shader < 0) {
        api->log(self, OP_MOD_LOG_ERROR,
                 "Could not compile shaders/rainbow.frag; see .build/shaders/rainbow.log");
        return 1;
    }

    openpete_mod_material_selector_t selector = openpete_mod_material_sel_any();
    selector.channel = OP_CHAN_PLAYER; // Spyro only, not the world or HUD
    g_material = api->material_register(self, &selector, shader);
    if (g_material < 0) {
        api->log(self, OP_MOD_LOG_ERROR, "Could not register Spyro material");
        return 2;
    }

    float initial[4] = { 0.0f, g_band_density, g_strength, 0.0f };
    api->material_set_params(self, g_material, initial, sizeof(initial));

    if (api->register_present_hook(self, rainbow_present) < 0) {
        api->log(self, OP_MOD_LOG_ERROR, "Could not register rainbow presentation hook");
        return 3;
    }

    api->log(self, OP_MOD_LOG_INFO, "Rainbow Spyro material loaded");
    api->ui_status(self, "Animated RGB enabled (Spyro player only)");
    return 0;
}
