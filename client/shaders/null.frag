#version 330 core

in vec3 FragPos;

out float FragDepth;

void main()
{
     FragDepth = length(FragPos);
}
