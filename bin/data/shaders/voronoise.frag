// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.


uniform vec2 iResolution;
uniform float iGlobalTime;
uniform sampler2D mask;

uniform float u_size; // 10-1
uniform float u_smooth; //0-1
uniform vec3 u_color;

vec2 hash( vec2 p ) { p=vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))); return fract(sin(p)*18.5453); }

// return distance, and cell id
vec2 voronoi( in vec2 x )
{
    vec2 n = floor( x );
    vec2 f = fract( x );
    
    vec3 m = vec3( 8.0 );
    for( int j=-1; j<=1; j++ )
        for( int i=-1; i<=1; i++ )
        {
            vec2  g = vec2( float(i), float(j) );
            vec2  o = hash( n + g );
            //vec2  r = g - f + o;
            vec2  r = g - f + (0.5+0.5*sin((iGlobalTime/5.)+6.2831*o));
            float d = dot( r, r );
            if( d<m.x )
                m = vec3( d, o );
        }
    
    return vec2( sqrt(m.x), m.y+m.z );
}

void main()
{
    float mask = texture2D(mask,(gl_FragCoord.xy / iResolution.xy)).r;
    vec4 finalColor = vec4(0.0);
    if(mask>0.0){
        
        vec2 p = gl_FragCoord.xy/max(iResolution.x,iResolution.y);
        
        // computer voronoi patterm
        vec2 c = voronoi( 19.0+36.0* u_size *p ); // u_size
        
        // colorize
        vec3 col = vec3(1.);//0.5 + 0.5*cos( c.y*6.2831 + vec3(0.0,1.0,2.0) );
        
        col *= clamp(u_smooth*100.0*c.x*c.x,0.0,1.0); // u_smooth 0-1
        col -= (1.0-smoothstep( 0.08, 0.09, c.x));
        float alpha =1.;
        
        col = 1. - col;
        
        //if(col.x<0.2){
        alpha = 1.-col.x;
        finalColor =vec4( col * u_color, 1. );
    }
    //}
    gl_FragColor =finalColor;
}