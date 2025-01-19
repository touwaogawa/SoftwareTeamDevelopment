#version 330 core

// Uniforms for world transform and view-proj
uniform mat4 model;
uniform mat4 viewProjection;

// Uniforms for animation frames
uniform vec2 frameSize;   // アトラス内の1フレームのサイズ (幅, 高さ)
uniform vec2 frameIndex;  // 表示するフレームのインデックス (x, y)

// Attribute 0 is position, 1 is normal, 2 is tex coords.
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

// Any vertex outputs (other than position)
out vec2 TexCoord;

void main()
{
	// Convert position to homogeneous coordinates
	vec4 pos = vec4(inPosition, 1.0);
	// Transform to position world space, then clip space
	gl_Position = pos * model * viewProjection;

	// Pass along the texture coordinate to frag shader
	TexCoord = (inTexCoord + frameIndex) * frameSize;
	// TexCoord = inTexCoord * frameSize + frameIndex;
}
