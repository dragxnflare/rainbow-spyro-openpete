#version 450
#extension GL_GOOGLE_include_directive : require
#include "openpete_psx_material.glsl"

// This shader applies only to OpenPete's 'player' rendering channel.
// Four floats fill the std140 vec4 from the C mod below.
layout(set = 3, binding = 1, std140) uniform RainbowSpyroParams {
    vec4 settings; // x: phase [0..1], y: band density, z: strength, w: unused
} rainbow;

// Fully saturated HSV rainbow converted to RGB. h = 0..1, wrapping.
vec3 rainbow_rgb(float h) {
    vec3 offset = vec3(0.0, 2.0 / 3.0, 1.0 / 3.0);
    vec3 p = abs(fract(h + offset) * 6.0 - 3.0);
    return clamp(p - 1.0, 0.0, 1.0);
}

// OpenPete supplies the base shaded fragment, and calls this function.
vec4 op_material(vec4 base) {
    vec2 xy = gl_FragCoord.xy;
    float density = rainbow.settings.y;

    // Soft diagonally-slanted rainbow waves, flowing continuously with phase.
    // Screen-space positioning is intentional and requires no game textures.
    float bend = 0.12 * sin(xy.x * 0.012 + xy.y * 0.007 - rainbow.settings.x * 6.2831853);
    float hue = fract(xy.y * density + xy.x * density * 0.40
                     + bend - rainbow.settings.x);
    vec3 color = rainbow_rgb(hue);

    // Retain a hint of the original face lighting instead of a flat neon fill.
    float luma = dot(base.rgb, vec3(0.2126, 0.7152, 0.0722));
    float light = mix(0.73, 1.08, clamp(luma * 1.6, 0.0, 1.0));
    vec3 rainbow_lit = min(color * light, vec3(1.0));

    // Preserve original alpha for holes/transparent parts of the model.
    vec3 result = mix(base.rgb, rainbow_lit, clamp(rainbow.settings.z, 0.0, 1.0));
    return vec4(result, base.a);
}
