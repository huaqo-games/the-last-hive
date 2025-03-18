#version 330

uniform sampler2D texture0;
uniform vec2 resolution;
uniform float strength;

in vec2 fragTexCoord;
out vec4 finalColor;

void main()
{
    vec2 uv = fragTexCoord;
    vec2 position = uv - vec2(0.5);
    float dist = length(position) * 2.0;  
    float vignette = 1.0 - strength * dist * dist;
    vignette = clamp(vignette, 0.0, 1.0);
    vec4 color = texture(texture0, uv);
    finalColor = vec4(color.rgb * vignette, color.a);
}
