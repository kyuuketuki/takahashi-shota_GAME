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
 79;
 0.11667;0.88994;-2.26186;,
 -1.72731;0.95586;-3.06039;,
 -2.48470;1.61416;2.67750;,
 -0.44312;-1.87627;-2.89575;,
 0.37188;-1.49800;-1.44687;,
 -0.37723;-0.88811;2.82568;,
 -2.65757;-1.74461;3.39371;,
 0.37188;-1.49800;-1.44687;,
 -0.44312;-1.87627;-2.89575;,
 0.37188;-1.49800;-1.44687;,
 -1.01111;-3.21788;-1.73500;,
 -0.16321;1.56501;2.61987;,
 -0.37723;-0.88811;2.82568;,
 -2.65757;-1.74461;3.39371;,
 -4.07355;-1.27537;-0.58248;,
 -6.74903;-0.88035;3.50896;,
 -7.01244;-3.75359;-2.22893;,
 -7.32528;-3.57185;3.21260;,
 -5.47304;-0.49322;-4.62452;,
 -6.89717;-3.54734;-4.63275;,
 -7.32528;-3.57185;3.21260;,
 -6.74903;-0.88035;3.50896;,
 -7.92624;0.64301;2.47993;,
 -4.36991;-5.40733;-3.90008;,
 -5.59652;-5.39175;3.45133;,
 -4.13116;-6.00921;-3.80130;,
 -5.19313;-5.98384;2.80921;,
 -5.47304;-0.49322;-4.62452;,
 -6.89717;-3.54734;-4.63275;,
 -7.62983;0.80774;-4.08119;,
 -8.01676;-3.46477;-4.40225;,
 -5.89284;-5.11189;-4.12235;,
 -6.76549;-5.63023;-4.25407;,
 -5.89284;-5.11189;-4.12235;,
 -4.13116;-6.00921;-3.80130;,
 -4.36991;-5.40733;-3.90008;,
 -4.07355;-1.27537;-0.58248;,
 -3.25030;-4.56028;-2.24540;,
 -1.01111;-3.21788;-1.73500;,
 -3.08567;-4.19795;-4.06473;,
 -1.01111;-3.21788;-1.73500;,
 -3.25030;-4.56028;-2.24540;,
 -4.97911;-3.40789;-2.25363;,
 -4.24639;-2.63384;-4.21291;,
 -5.47304;-0.49322;-4.62452;,
 -0.44312;-1.87627;-2.89575;,
 -4.24639;-2.63384;-4.21291;,
 -4.24639;-2.63384;-4.21291;,
 -0.44312;-1.87627;-2.89575;,
 -7.87682;-5.84385;-3.25797;,
 -7.61340;-5.63023;-4.29523;,
 -7.99204;-6.41202;-3.76837;,
 -7.52285;-6.42007;-4.12235;,
 -5.60477;-5.39925;-2.60762;,
 -5.56361;-5.46553;-4.01533;,
 -4.24639;-2.63384;-4.21291;,
 -6.06572;-4.07405;-3.95771;,
 -4.97911;-3.40789;-2.25363;,
 -7.21824;-4.98833;-3.14271;,
 -6.06572;-4.07405;-3.95771;,
 -9.01291;-3.40789;2.22472;,
 -5.89284;-5.11189;-4.12235;,
 -6.83956;-4.59283;3.26199;,
 -6.83956;-4.59283;3.26199;,
 -7.35820;-5.67110;2.43876;,
 -5.59652;-5.39175;3.45133;,
 -5.19313;-5.98384;2.80921;,
 -7.21824;-4.98833;-3.14271;,
 -5.60477;-5.39925;-2.60762;,
 -4.97911;-3.40789;-2.25363;,
 -3.25030;-4.56028;-2.24540;,
 -7.52285;-6.42007;-4.12235;,
 -7.60519;-6.42007;-3.43908;,
 -7.61340;-5.63023;-4.29523;,
 -7.87682;-5.84385;-3.25797;,
 -7.39115;-6.32974;-3.02746;,
 -7.60519;-6.42007;-3.43908;,
 -7.39115;-6.32974;-3.02746;,
 -7.39115;-6.32974;-3.02746;;
 
 78;
 3;0,1,2;,
 3;3,0,4;,
 3;0,3,1;,
 3;5,6,7;,
 3;8,9,10;,
 3;11,2,12;,
 3;13,12,2;,
 3;14,15,16;,
 3;17,16,15;,
 3;18,14,19;,
 3;16,19,14;,
 3;20,21,22;,
 3;23,24,25;,
 3;26,25,24;,
 3;27,28,29;,
 3;29,28,30;,
 3;19,16,31;,
 3;30,28,32;,
 3;33,32,28;,
 3;32,33,34;,
 3;35,34,33;,
 3;36,37,38;,
 3;39,40,41;,
 3;22,21,2;,
 3;13,2,21;,
 3;3,27,1;,
 3;29,1,27;,
 3;14,18,42;,
 3;43,42,18;,
 3;7,6,38;,
 3;36,38,6;,
 3;14,6,15;,
 3;44,45,46;,
 3;39,47,48;,
 3;49,50,51;,
 3;52,51,50;,
 3;36,42,37;,
 3;48,40,39;,
 3;41,53,39;,
 3;54,39,53;,
 3;55,56,57;,
 3;58,57,56;,
 3;39,54,47;,
 3;59,47,54;,
 3;60,22,30;,
 3;60,20,22;,
 3;16,17,61;,
 3;62,61,17;,
 3;20,60,63;,
 3;64,63,60;,
 3;61,62,23;,
 3;24,23,62;,
 3;34,64,32;,
 3;63,64,65;,
 3;66,65,64;,
 3;67,68,69;,
 3;70,69,68;,
 3;54,53,71;,
 3;72,71,53;,
 3;58,56,49;,
 3;50,49,56;,
 3;59,54,73;,
 3;71,73,54;,
 3;67,74,68;,
 3;75,68,74;,
 3;64,30,32;,
 3;66,64,34;,
 3;22,2,1;,
 3;30,22,29;,
 3;64,60,30;,
 3;11,0,2;,
 3;22,1,29;,
 3;76,51,52;,
 3;77,72,53;,
 3;49,76,78;,
 3;76,49,51;,
 3;0,11,5;,
 3;5,4,0;;
 
 MeshMaterialList {
  2;
  78;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\C++Game\\MapTesting\\MapTesting\\data\\TEXTURE\\player.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  92;
  0.048889;0.991612;-0.119645;,
  0.002643;0.959417;-0.281979;,
  -0.024023;0.991837;-0.125227;,
  0.947079;-0.315057;-0.061488;,
  0.602082;-0.142831;-0.785555;,
  0.387280;-0.900782;0.196485;,
  0.319850;-0.925163;0.204375;,
  0.709462;-0.697800;-0.098683;,
  0.026455;0.081282;0.996340;,
  0.514010;-0.857587;-0.018378;,
  0.791683;-0.560048;0.244100;,
  0.754814;-0.639064;0.147827;,
  0.952711;0.297512;0.061880;,
  0.471627;0.078088;-0.878334;,
  0.776695;-0.594558;-0.207955;,
  -0.432479;0.215483;0.875516;,
  0.593573;0.801699;0.070355;,
  0.803354;0.580993;0.130650;,
  0.896790;0.417807;0.145622;,
  0.882347;0.449286;0.140024;,
  -0.089177;0.256005;-0.962553;,
  -0.204864;-0.048857;-0.977570;,
  0.722811;0.689831;0.040942;,
  0.065841;-0.127754;-0.989618;,
  -0.127695;-0.367975;0.921026;,
  0.523785;-0.838634;-0.149476;,
  -0.474955;-0.161508;0.865063;,
  -0.484292;-0.289421;-0.825649;,
  -0.804940;0.563423;-0.186079;,
  -0.868800;0.316546;-0.380769;,
  -0.848407;0.056187;-0.526354;,
  -0.237795;-0.233622;-0.942801;,
  0.431942;-0.901864;-0.008196;,
  0.445272;-0.893698;0.055098;,
  -0.670545;0.739505;-0.059171;,
  -0.675714;0.722828;-0.144671;,
  -0.972503;-0.182546;-0.144617;,
  0.583754;0.810632;0.045898;,
  -0.583180;-0.714697;0.386147;,
  0.304554;-0.952495;-0.000429;,
  -0.571352;-0.192620;0.797781;,
  0.940360;0.038623;-0.337980;,
  0.373513;0.115861;-0.920361;,
  0.036843;0.248082;0.968038;,
  0.096886;0.139954;0.985407;,
  0.118738;0.201223;0.972322;,
  -0.548635;-0.025438;0.835675;,
  -0.238971;0.264753;0.934237;,
  -0.519235;-0.234727;-0.821765;,
  -0.091893;-0.042182;-0.994875;,
  0.825095;0.558184;0.087458;,
  0.807452;0.587253;0.056172;,
  0.175936;-0.100433;-0.979265;,
  0.143821;-0.070801;-0.987068;,
  0.121897;-0.113474;-0.986035;,
  -0.138955;-0.474773;0.869070;,
  0.058882;-0.439085;0.896514;,
  0.443605;-0.885802;-0.136271;,
  -0.930040;0.123816;0.345970;,
  -0.723709;-0.505124;-0.470207;,
  -0.511849;-0.855215;0.081351;,
  -0.207614;-0.977334;-0.041403;,
  0.218819;0.020150;-0.975557;,
  0.163136;0.027631;-0.986216;,
  -0.611458;0.786991;0.082246;,
  -0.601915;0.795222;0.072943;,
  0.041281;-0.049171;-0.997937;,
  -0.002770;0.040376;-0.999181;,
  -0.979105;0.180025;-0.094574;,
  -0.974449;-0.199459;-0.103277;,
  -0.525901;-0.152026;0.836849;,
  -0.487879;-0.320760;0.811842;,
  -0.139544;-0.990043;-0.018521;,
  -0.139276;-0.990083;-0.018380;,
  -0.555720;-0.829596;-0.054280;,
  -0.314215;-0.621065;0.718016;,
  -0.186458;-0.935563;0.299926;,
  -0.311080;0.015940;0.950250;,
  -0.257713;0.009290;0.966177;,
  0.291379;-0.955930;0.036012;,
  0.139401;-0.054635;-0.988728;,
  -0.516702;-0.199246;0.832658;,
  -0.099844;0.993448;-0.055616;,
  -0.994728;0.093286;-0.042596;,
  0.017596;0.990557;-0.135970;,
  -0.029188;0.999291;0.023771;,
  -0.018869;-0.999819;-0.002274;,
  0.470860;-0.880699;-0.051576;,
  -0.653229;-0.489494;0.577657;,
  -0.574617;-0.479367;0.663342;,
  0.994375;-0.081030;0.068215;,
  0.993283;0.037401;0.109500;;
  78;
  3;0,1,2;,
  3;4,41,3;,
  3;41,4,42;,
  3;5,6,5;,
  3;4,3,7;,
  3;8,43,44;,
  3;45,44,43;,
  3;9,10,11;,
  3;12,11,10;,
  3;13,9,14;,
  3;11,14,9;,
  3;46,47,15;,
  3;16,17,18;,
  3;19,18,17;,
  3;48,49,20;,
  3;20,49,21;,
  3;50,51,22;,
  3;21,49,23;,
  3;52,23,49;,
  3;23,52,53;,
  3;54,53,52;,
  3;55,24,56;,
  3;25,7,57;,
  3;15,47,43;,
  3;45,43,47;,
  3;4,13,42;,
  3;20,1,13;,
  3;58,58,26;,
  3;27,59,48;,
  3;3,6,7;,
  3;60,60,60;,
  3;9,6,61;,
  3;13,4,62;,
  3;63,62,4;,
  3;28,29,30;,
  3;31,30,29;,
  3;55,26,24;,
  3;4,7,25;,
  3;57,32,25;,
  3;33,25,32;,
  3;64,34,65;,
  3;35,65,34;,
  3;63,66,62;,
  3;67,27,66;,
  3;36,68,69;,
  3;70,46,15;,
  3;51,12,22;,
  3;37,22,12;,
  3;46,70,71;,
  3;38,71,70;,
  3;22,37,16;,
  3;17,16,37;,
  3;72,73,74;,
  3;71,38,75;,
  3;76,75,38;,
  3;77,78,26;,
  3;24,26,78;,
  3;33,32,79;,
  3;39,79,32;,
  3;35,34,28;,
  3;29,28,34;,
  3;67,66,80;,
  3;31,80,66;,
  3;77,81,78;,
  3;40,78,81;,
  3;38,69,74;,
  3;76,38,72;,
  3;82,2,1;,
  3;69,68,83;,
  3;38,36,69;,
  3;84,0,2;,
  3;82,1,85;,
  3;39,86,79;,
  3;87,39,32;,
  3;81,88,40;,
  3;88,81,89;,
  3;41,90,91;,
  3;91,3,41;;
 }
 MeshTextureCoords {
  79;
  0.353400;0.204800;,
  0.353200;0.219000;,
  0.298700;0.214300;,
  0.365100;0.217300;,
  0.365200;0.203100;,
  0.223000;0.207300;,
  0.222500;0.240500;,
  0.250400;0.206300;,
  0.308600;0.248400;,
  0.308600;0.251100;,
  0.309900;0.250800;,
  0.299400;0.203500;,
  0.290600;0.208600;,
  0.290200;0.217500;,
  0.265900;0.261300;,
  0.222600;0.270300;,
  0.267300;0.295000;,
  0.222700;0.293800;,
  0.287700;0.275800;,
  0.285200;0.296400;,
  0.289600;0.290100;,
  0.289300;0.259700;,
  0.296500;0.260200;,
  0.267200;0.314300;,
  0.222700;0.312500;,
  0.267800;0.323100;,
  0.222100;0.325100;,
  0.365100;0.260500;,
  0.365400;0.291800;,
  0.357800;0.262100;,
  0.356100;0.292500;,
  0.285200;0.306700;,
  0.358000;0.309400;,
  0.364500;0.310800;,
  0.360500;0.325600;,
  0.365000;0.326500;,
  0.281900;0.247400;,
  0.287600;0.249700;,
  0.282000;0.209000;,
  0.317300;0.260200;,
  0.320900;0.245100;,
  0.322400;0.258100;,
  0.278500;0.259400;,
  0.287800;0.262800;,
  0.287400;0.252000;,
  0.280900;0.258900;,
  0.288000;0.261100;,
  0.304700;0.253000;,
  0.315900;0.242700;,
  0.279600;0.229300;,
  0.279600;0.228400;,
  0.280000;0.228800;,
  0.280300;0.228400;,
  0.324100;0.291800;,
  0.314400;0.290300;,
  0.277800;0.228200;,
  0.279000;0.228400;,
  0.277800;0.229300;,
  0.279000;0.229300;,
  0.304000;0.289100;,
  0.294700;0.293000;,
  0.266400;0.304800;,
  0.222700;0.306300;,
  0.289200;0.303200;,
  0.296700;0.309000;,
  0.288900;0.326500;,
  0.296500;0.326300;,
  0.282200;0.227000;,
  0.284200;0.221600;,
  0.282400;0.223900;,
  0.282000;0.221300;,
  0.315700;0.326800;,
  0.320700;0.327400;,
  0.309000;0.326000;,
  0.284900;0.227400;,
  0.285100;0.223700;,
  0.280300;0.228800;,
  0.324200;0.326600;,
  0.280300;0.229100;;
 }
}
