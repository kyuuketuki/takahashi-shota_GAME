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
 53;
 4.27902;-0.15751;-0.29901;,
 4.27902;-4.09301;-0.29901;,
 3.13236;-4.09301;-2.69197;,
 3.13236;-0.15751;-3.14469;,
 -0.71478;-4.09301;-4.14155;,
 -0.71478;-0.15751;-4.59425;,
 -2.96580;-4.09301;-2.69197;,
 -2.96580;-0.15751;-3.14469;,
 -4.11248;-4.09301;-0.29901;,
 -4.11248;-0.15751;-0.29901;,
 -2.96580;-4.09301;3.20059;,
 -2.96580;-0.15751;3.20059;,
 -0.71478;-4.09301;4.65017;,
 -0.71478;-0.15751;4.65017;,
 3.13236;-4.09301;3.20059;,
 3.13236;-0.15751;3.20059;,
 4.27902;-4.09301;-0.29901;,
 4.27902;-0.15751;-0.29901;,
 4.27902;-8.02849;-0.29901;,
 3.13236;-8.02849;-2.18895;,
 -0.71478;-8.02849;-3.63853;,
 -2.96580;-8.02849;-2.18895;,
 -4.11248;-8.02849;-0.29901;,
 -2.96580;-8.02849;3.20059;,
 -0.71478;-8.02849;4.65017;,
 3.13236;-8.02849;3.20059;,
 4.27902;-8.02849;-0.29901;,
 3.87662;-11.96399;-0.29901;,
 2.72994;-11.96399;-2.18895;,
 -0.71478;-11.96399;-3.22983;,
 -2.96580;-11.96399;-2.18895;,
 -4.11248;-11.96399;-0.29901;,
 -2.96580;-11.96399;3.20059;,
 -0.71478;-11.96399;4.30433;,
 2.72994;-11.96399;3.20059;,
 3.87662;-11.96399;-0.29901;,
 2.18766;-16.13151;-0.29901;,
 1.33754;-16.13151;-1.78687;,
 -0.71478;-16.13151;-2.86155;,
 -2.76712;-16.13151;-1.78687;,
 -3.61722;-16.13151;-0.29901;,
 -2.76712;-16.13151;2.29549;,
 -0.71478;-16.13151;3.37017;,
 1.33754;-16.13151;2.29549;,
 2.18766;-16.13151;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;,
 -0.71478;-0.15751;-0.29901;;
 
 40;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;1,18,19,2;,
 4;2,19,20,4;,
 4;4,20,21,6;,
 4;6,21,22,8;,
 4;8,22,23,10;,
 4;10,23,24,12;,
 4;12,24,25,14;,
 4;14,25,26,16;,
 4;18,27,28,19;,
 4;19,28,29,20;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;25,34,35,26;,
 4;27,36,37,28;,
 4;28,37,38,29;,
 4;29,38,39,30;,
 4;30,39,40,31;,
 4;31,40,41,32;,
 4;32,41,42,33;,
 4;33,42,43,34;,
 4;34,43,44,35;,
 3;45,0,3;,
 3;46,3,5;,
 3;47,5,7;,
 3;48,7,9;,
 3;49,9,11;,
 3;50,11,13;,
 3;51,13,15;,
 3;52,15,17;;
 
 MeshMaterialList {
  1;
  40;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  40;
  0.000000;1.000000;0.000000;,
  0.998728;-0.011508;-0.049099;,
  0.686700;-0.069739;-0.723588;,
  -0.105281;-0.113644;-0.987928;,
  -0.759419;-0.061513;-0.647688;,
  -0.998728;-0.011509;-0.049100;,
  -0.791428;0.000000;0.611263;,
  -0.105692;0.000000;0.994399;,
  0.722391;0.000000;0.691485;,
  0.997517;-0.013260;-0.069167;,
  0.671589;-0.074005;-0.737219;,
  -0.105236;-0.119866;-0.987197;,
  -0.745865;-0.065521;-0.662867;,
  -0.997517;-0.013260;-0.069168;,
  -0.791427;0.000000;0.611263;,
  -0.105692;0.000000;0.994399;,
  0.993132;-0.057891;-0.101675;,
  0.640083;-0.080237;-0.764105;,
  -0.096439;-0.093084;-0.990977;,
  -0.712465;-0.046084;-0.700192;,
  -0.994779;-0.007559;-0.101769;,
  -0.782504;-0.009851;0.622568;,
  -0.097472;-0.026796;0.994877;,
  0.717128;-0.043538;0.695580;,
  0.964843;-0.239032;-0.109279;,
  0.628597;-0.162565;-0.760551;,
  -0.061624;-0.092335;-0.993819;,
  -0.684882;-0.060362;-0.726150;,
  -0.992199;-0.056995;-0.110872;,
  -0.763766;-0.095236;0.638429;,
  -0.063492;-0.150553;0.986561;,
  0.704733;-0.211725;0.677145;,
  0.923114;-0.370532;-0.102793;,
  0.629449;-0.241280;-0.738632;,
  -0.035288;-0.123877;-0.991670;,
  -0.676971;-0.098330;-0.729411;,
  -0.987719;-0.113575;-0.107288;,
  -0.749737;-0.170693;0.639342;,
  -0.037019;-0.246428;0.968454;,
  0.688259;-0.330240;0.645943;;
  40;
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,8;,
  4;8,8,9,1;,
  4;9,16,17,10;,
  4;10,17,18,11;,
  4;11,18,19,12;,
  4;12,19,20,13;,
  4;13,20,21,14;,
  4;14,21,22,15;,
  4;15,22,23,8;,
  4;8,23,16,9;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,24,16;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,32,24;,
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
  53;
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;;
 }
}
