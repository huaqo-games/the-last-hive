✅ Notes for using in Raylib

Vertex shader: You can use the default Raylib one (default.vs).

Time uniform: Update each frame in C:

float t = GetTime();
SetShaderValue(shader, GetShaderLocation(shader, "time"), &t, SHADER_UNIFORM_FLOAT);

Other textures: Bind them using SetShaderTexture(shader, loc, texture).

If you want, I can also write a full Raylib C snippet showing exactly how to load this shader and set all the textures and uniforms.

Do you want me to do that?
