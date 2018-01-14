#!/bin/bash
npm install; 
#转换
node ./csv2json.js;
#拷贝
cp -r ./outputPath/* ../../HeroLegend_assets/res/conf/