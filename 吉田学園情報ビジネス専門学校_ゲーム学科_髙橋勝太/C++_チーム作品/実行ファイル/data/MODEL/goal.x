xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 88;
 -0.29600;11.77290;-45.26846;,
 18.26622;11.77290;-41.32296;,
 18.26622;3.21506;-41.32296;,
 -0.29600;3.21506;-45.26846;,
 33.61885;11.77290;-30.16862;,
 33.61885;3.21506;-30.16862;,
 43.10729;11.77290;-13.73414;,
 43.10729;3.21506;-13.73414;,
 45.09093;11.77290;5.13880;,
 45.09093;3.21506;5.13880;,
 39.22676;11.77290;23.18691;,
 39.22676;3.21506;23.18691;,
 26.52871;11.77290;37.28951;,
 26.52871;3.21506;37.28951;,
 9.19245;11.77290;45.00810;,
 9.19245;3.21506;45.00810;,
 -9.78445;11.77290;45.00810;,
 -9.78445;3.21506;45.00810;,
 -27.12072;11.77290;37.28950;,
 -27.12072;3.21506;37.28950;,
 -39.81876;11.77290;23.18690;,
 -39.81876;3.21506;23.18690;,
 -45.68293;11.77290;5.13880;,
 -45.68293;3.21506;5.13880;,
 -43.69930;11.77290;-13.73415;,
 -43.69930;3.21506;-13.73415;,
 -34.21084;11.77290;-30.16862;,
 -34.21084;3.21506;-30.16862;,
 -18.85820;11.77290;-41.32297;,
 -18.85820;3.21506;-41.32297;,
 -0.29600;11.77290;-45.26846;,
 -0.29600;3.21506;-45.26846;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;11.77290;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;3.21506;0.36844;,
 -0.29600;237.42222;87.83897;,
 -0.29600;61.46733;-0.11900;,
 61.89970;237.42222;62.07666;,
 -0.29600;61.46733;-0.11900;,
 87.66203;237.42222;-0.11901;,
 -0.29600;61.46733;-0.11900;,
 61.89970;237.42222;-62.31469;,
 -0.29600;61.46733;-0.11900;,
 -0.29600;237.42222;-88.07703;,
 -0.29600;61.46733;-0.11900;,
 -62.49169;237.42222;-62.31468;,
 -0.29600;61.46733;-0.11900;,
 -88.25401;237.42222;-0.11901;,
 -0.29600;61.46733;-0.11900;,
 -62.49169;237.42222;62.07665;,
 -0.29600;61.46733;-0.11900;,
 -0.29600;237.42222;87.83897;,
 -0.29600;237.42222;-0.11901;,
 -0.29600;237.42222;87.83897;,
 61.89970;237.42222;62.07666;,
 87.66203;237.42222;-0.11901;,
 61.89970;237.42222;-62.31469;,
 -0.29600;237.42222;-88.07703;,
 -62.49169;237.42222;-62.31468;,
 -88.25401;237.42222;-0.11901;,
 -62.49169;237.42222;62.07665;;
 
 61;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 3;32,1,0;,
 3;33,4,1;,
 3;34,6,4;,
 3;35,8,6;,
 3;36,10,8;,
 3;37,12,10;,
 3;38,14,12;,
 3;39,16,14;,
 3;40,18,16;,
 3;41,20,18;,
 3;42,22,20;,
 3;43,24,22;,
 3;44,26,24;,
 3;45,28,26;,
 3;46,30,28;,
 3;47,3,2;,
 3;48,2,5;,
 3;49,5,7;,
 3;50,7,9;,
 3;51,9,11;,
 3;52,11,13;,
 3;53,13,15;,
 3;54,15,17;,
 3;55,17,19;,
 3;56,19,21;,
 3;57,21,23;,
 3;58,23,25;,
 3;59,25,27;,
 3;60,27,29;,
 3;61,29,31;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;68,69,70;,
 3;70,71,72;,
 3;72,73,74;,
 3;74,75,76;,
 3;76,77,78;,
 3;79,80,81;,
 3;79,81,82;,
 3;79,82,83;,
 3;79,83,84;,
 3;79,84,85;,
 3;79,85,86;,
 3;79,86,87;,
 3;79,87,80;;
 
 MeshMaterialList {
  1;
  61;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.765490;0.175686;0.800000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.956863;0.219608;;
  }
 }
 MeshNormals {
  25;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.406736;0.000000;-0.913546;,
  0.743145;0.000000;-0.669131;,
  0.951056;0.000000;-0.309017;,
  0.994522;0.000000;0.104528;,
  0.866025;0.000000;0.500000;,
  0.587785;0.000000;0.809017;,
  0.207911;0.000000;0.978148;,
  -0.207912;0.000000;0.978148;,
  -0.587785;0.000000;0.809017;,
  -0.866026;0.000000;0.500000;,
  -0.994522;0.000000;0.104528;,
  -0.951056;0.000000;-0.309017;,
  -0.743145;0.000000;-0.669131;,
  -0.406736;0.000000;-0.913546;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-0.447134;0.894467;,
  0.632483;-0.447134;0.632484;,
  0.894467;-0.447135;0.000000;,
  0.632483;-0.447134;-0.632484;,
  -0.000000;-0.447135;-0.894467;,
  -0.632484;-0.447134;-0.632483;,
  -0.894467;-0.447135;0.000000;,
  -0.632483;-0.447134;0.632484;;
  61;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,1,1,15;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;17,18,18;,
  3;18,18,19;,
  3;19,20,20;,
  3;20,20,21;,
  3;21,22,22;,
  3;22,22,23;,
  3;23,24,24;,
  3;24,24,17;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;;
 }
 MeshTextureCoords {
  88;
  0.000000;0.000000;,
  0.066667;0.000000;,
  0.066667;1.000000;,
  0.000000;1.000000;,
  0.133333;0.000000;,
  0.133333;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.266667;0.000000;,
  0.266667;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.466667;0.000000;,
  0.466667;1.000000;,
  0.533333;0.000000;,
  0.533333;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.733333;0.000000;,
  0.733333;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.866667;0.000000;,
  0.866667;1.000000;,
  0.933333;0.000000;,
  0.933333;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.033333;0.000000;,
  0.100000;0.000000;,
  0.166667;0.000000;,
  0.233333;0.000000;,
  0.300000;0.000000;,
  0.366667;0.000000;,
  0.433333;0.000000;,
  0.500000;0.000000;,
  0.566667;0.000000;,
  0.633333;0.000000;,
  0.700000;0.000000;,
  0.766667;0.000000;,
  0.833333;0.000000;,
  0.900000;0.000000;,
  0.966667;0.000000;,
  0.033333;1.000000;,
  0.100000;1.000000;,
  0.166667;1.000000;,
  0.233333;1.000000;,
  0.300000;1.000000;,
  0.366667;1.000000;,
  0.433333;1.000000;,
  0.500000;1.000000;,
  0.566667;1.000000;,
  0.633333;1.000000;,
  0.700000;1.000000;,
  0.766667;1.000000;,
  0.833333;1.000000;,
  0.900000;1.000000;,
  0.966667;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
