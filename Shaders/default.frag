
#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D textureUni0;
uniform sampler2D textureUni1;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;  
uniform mat3 normalMat; // matrix to transform normals

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform Material material;
uniform Light light;  


vec4 pointLight(){
    vec3 lightVec = normalize(light.position - FragPos);
    float dist = length(lightVec);
    float a = 3.0;
    float b= 0.7;
    float inten = 1.0 / (a* dist * dist + b * dist + 1.0f);

    // ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = Normal;
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return ( texture(textureUni0, TexCoord) * (diffuse * inten + ambient) + texture(textureUni1, TexCoord).r * specular * inten) * vec4(lightColor,1.0f);
}

vec4 pointLight2(){
    vec3 lightVec = normalize(light.position - FragPos);
    float dist = length(lightVec);
    float attenuation = 1.0 / light.constant + light.linear * dist + light.quadratic * (dist * dist);
    

     // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    // diffuse 
    vec3 norm = Normal;
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;  

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;  
  	
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    return ( vec4(result, 1.0));
}

vec4 spotLight(){
    vec3 lightDir = normalize(light.position - FragPos);
    float dist = length(lightDir);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
    // diffuse 
    vec3 norm = Normal;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;  

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);       
   
    diffuse  *= intensity;
    specular *= intensity;
    diffuse *= attenuation;
    specular *= attenuation;
    vec3 debugColor = vec3(dot(lightDir, normalize(-light.direction)));

    vec3 result =  ambient + diffuse + specular ;
    return (vec4(result, 1.0));
    
}



vec4 dirLight()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    return ( vec4(result, 1.0));
}



void main()
{
    //FragColor = pointLight();
    FragColor = vec4(Normal * 0.5 + 0.5, 1.0); 
    //FragColor = spotLight();
    //the FragColor is auto sent to the framebuffer color attachment

}
