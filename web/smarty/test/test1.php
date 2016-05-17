<?php
require ("../Smarty.class.php");

//template_c要可写，否则修改模板之后，浏览器解析报错
$smarty = new Smarty();
$smarty->template_dir = "../template";//html模板地址
$smarty->compile_dir = "../template_c";//模板编译生成的文件
$smarty->assign("file_include","<title>smarty应用</title>");
$smarty->assign("style_include","");
$smarty->assign("body","");
$smarty->display("test1.tpl");

?>
