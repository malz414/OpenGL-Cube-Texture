#version 410 core
out vec4 FragColor;



uniform sampler2D image;
uniform int hor;
in vec2 uv;


uniform float weights[22] = {
0.016763484915651723, 0.01753817278195756, 0.01830827190172033, 0.019070115902322094, 0.0198199372299882,
0.020553896754688848, 0.021268115382044078, 0.02195870733083133, 0.022621814696803258, 0.023253642891173213,
0.023850496516196473, 0.024408815221454452, 0.024925209073393424, 0.025396492967770915, 0.0258197196202193,
0.02619221068423102, 0.026511585568391595, 0.026775787555338278, 0.026983106863243615, 0.027132200335927083,
0.027222107499168723, 0.02725221661496892,} ;

int r = 21;
float bias = 1.10f;


//BLUR W LINES
//uniform float weights[] = {

//0.003765,	0.015019,	0.023792,	0.015019,	0.003765,
//0.015019,	0.059912,	0.094907,	0.059912,	0.015019,
//0.023792,	0.094907,	0.150342,	0.094907,	0.023792,
//0.015019,	0.059912,	0.094907,	0.059912,	0.015019,
//0.003765,	0.015019,	0.023792,	0.015019,	0.003765,} ;

//int r = 17;
//float bias = .80f;

void main()
{             
 vec2 textureOffset = 1.0/textureSize(image, 0);
 vec3 color = texture(image, uv).xyz * (weights[0]*bias);
 if (hor ==1){
 	 for(int i = 1 ; i < r ; i++){
	 	 color = color +texture (image, uv + vec2(textureOffset.x * i, 0.0)).xyz * (weights[i]*bias);
	 	 color = color +texture (image, uv - vec2(textureOffset.x * i, 0.0)).xyz * (weights[i]*bias);
	 }
 }

 else{
 	 for(int i = 1 ; i < r ; i++){
	 color = color +texture (image, uv + vec2(textureOffset.y * i, 0.0)).xyz * (weights[i]*bias);
	 color = color +texture (image, uv - vec2(textureOffset.y * i, 0.0)).xyz * (weights[i]*bias);
	 }
 }
  
    FragColor = vec4(color, 1.0); // perspective
    
}

