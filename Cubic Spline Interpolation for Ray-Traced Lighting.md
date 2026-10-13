# Cubic Spline Interpolation for Ray-Traced Lighting

Oct 13, 2026 · @Neo

## Overview

Cubic splines reduce how many rays you trace; they do not speed up ray–triangle intersection. That job belongs to a BVH. The approach: compute lighting at sparse sample points, interpolate the rest, and trade a small, measurable error for a large drop in ray count. Measuring that error is the numerical analysis part.

## Where splines fit in the lighting pipeline

Screen-space upsampling or a probe grid is the most defensible project; the other two are smaller add-ons.

| Use | What gets traced | What the spline does | Main caveat |
| --- | --- | --- | --- |
| Screen-space upsampling | Lighting at 1/4 or 1/16 resolution | Bicubic reconstruction to full resolution | Overshoot rings at shadow edges |
| Irradiance probe grid (DDGI-style) | Lighting into a 3D grid of probes | Tricubic B-spline instead of trilinear for C² smoothness | 64 taps instead of 8, or 8 with the GPU Gems trick |
| Temporal interpolation | Each probe every N frames | Interpolates between keyframes | Only suits slowly moving lights |
| Tabulating expensive functions | Nothing extra | Fits 1D terms: attenuation, Fresnel, sky/atmosphere integrals | Accuracy limited by table density |

For upsampling, compare natural cubic, Catmull-Rom, and monotone cubic (Fritsch–Carlson). The monotone variant preserves monotonicity and removes the overshoot, which makes a good class topic on its own.

## Ties to MACM 316

The strongest result is an empirical error-convergence plot that matches the theoretical orders.

- **Tridiagonal solve.** Natural or clamped spline coefficients come from a tridiagonal system. It is strictly diagonally dominant, so the Thomas algorithm (O(n), no pivoting) is stable, and you can prove it.
- **Error analysis.** Cubic spline error is O(h⁴); linear interpolation is O(h²). Plot RMSE against a fully ray-traced reference while varying probe spacing or downsample factor. Log-log slopes should come out near 4 and 2.
- **Hermite vs. spline.** Ward's irradiance caching uses gradient information, which is effectively Hermite interpolation. It makes a clean comparison point.
- **Floating point.** Compare float32 on the GPU against float64 references.

```latex
\max_{a \le x \le b} |f(x) - S(x)| \le \frac{5}{384} \, h^4 \max_{a \le x \le b} |f^{(4)}(x)|
```

This is the clamped cubic spline bound, the one your plot should confirm.

## Implementation notes

OpenGL core has no hardware ray tracing, so the tracer runs in compute shaders (GL 4.3+) with the BVH stored in SSBOs. Build the BVH on the CPU first: it is the real accelerator, and you need it regardless of interpolation.

## Resources

Cited from memory, not looked up; check editions and chapter numbers.

| Side | Reference | Use it for |
| --- | --- | --- |
| Numerical | Burden & Faires, *Numerical Analysis*, Ch. 3 | Natural/clamped spline derivation and error bound |
| Numerical | Fritsch & Carlson (1980), "Monotone Piecewise Cubic Interpolation," *SIAM J. Numer. Anal.* | Overshoot-free interpolation |
| Numerical | *Numerical Recipes*, §3.3 | Compact spline construction code |
| Numerical | Unser (1999), "Splines: A Perfect Fit for Signal and Image Processing," *IEEE Signal Processing Magazine* | B-splines on 2D/3D grids |
| Graphics | Shirley, *Ray Tracing in One Weekend* series (free online) | Ray tracer fundamentals |
| Graphics | Pharr, Jakob, Humphreys, *Physically Based Rendering* 4th ed. ([pbr-book.org](https://pbr-book.org)) | BVH, sampling and reconstruction |
| Graphics | Jacco Bikker, "How to build a BVH" blog series | Practical, GPU-oriented BVH |
| Graphics | Sigg & Hadwiger, "Fast Third-Order Texture Filtering," *GPU Gems 2* Ch. 20 | Bicubic/tricubic B-spline via hardware linear filtering |
| Graphics | Majercik et al. (2019), "Dynamic Diffuse Global Illumination with Ray-Traced Irradiance Fields," *JCGT* | Probe-grid approach |
| Graphics | Ward & Heckbert (1992), "Irradiance Gradients" | Interpolating ray-traced lighting with error control |
| Graphics | LearnOpenGL, compute shader chapters | GL-specific setup |

## Suggested project path

Four steps give a complete class project:

1. Build a CPU BVH and upload it to SSBOs.
2. Write a compute-shader path tracer for indirect diffuse into a low-res buffer.
3. Implement three upsamplers: bilinear, natural cubic, monotone cubic.
4. Plot error against ray budget for each, using a full-resolution trace as the reference.
