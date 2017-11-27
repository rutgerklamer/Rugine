#version 410 core

out vec2 texCoords;

void main(void)
{
  const vec4 vertices[] = vec4[](vec4( -1.0, 1.0, 0.5, 1),
                                 vec4(-1.0, -1.0, 0.5, 1),
                                 vec4( 1.0,  -1.0, 0.5, 1),

                                 vec4( -1.0, 1.0, 0.5, 1),
                                 vec4(1.0, -1.0, 0.5, 1),
                                 vec4( 1.0,  1.0, 0.5, 1)
                                 );

const vec2 TexCoords[] = vec2[](vec2(0,1),
                               vec2(0,0),
                               vec2(1,0),

                               vec2(0,1),
                               vec2(1,0),
                               vec2(1,1)
                               );
 texCoords = TexCoords[gl_VertexID];
 gl_Position = vertices[gl_VertexID];
}
