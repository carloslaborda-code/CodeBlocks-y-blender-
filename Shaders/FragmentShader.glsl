precision mediump float; // Precisión media

   // in: color del vertex shader
varying vec4 v_Color; // in: color del vertex shader
varying float v_specular;
void main()
{
gl_FragColor = v_Color + vec4(1,1,1,1)*v_specular;
}
