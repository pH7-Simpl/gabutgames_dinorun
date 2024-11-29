#version 330 core

in vec2 TexCoord;    // Texture coordinates passed from vertex shader

// Texture samplers
uniform sampler2D ourTexture;

// The uniform color (u_Color) that will be set from the application (C++ code)
uniform vec4 u_Color;

void main()
{
    // Apply texture color with the uniform color (u_Color)
    gl_FragColor = texture(ourTexture, TexCoord) * u_Color;
}
