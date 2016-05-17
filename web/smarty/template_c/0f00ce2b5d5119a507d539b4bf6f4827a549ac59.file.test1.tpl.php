<?php /* Smarty version Smarty-3.1.21-dev, created on 2015-03-26 10:50:31
         compiled from "smarty/template/test1.tpl" */ ?>
<?php /*%%SmartyHeaderCode:639762524551372a39c7960-21188275%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '0f00ce2b5d5119a507d539b4bf6f4827a549ac59' => 
    array (
      0 => 'smarty/template/test1.tpl',
      1 => 1427338227,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '639762524551372a39c7960-21188275',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.21-dev',
  'unifunc' => 'content_551372a3be0104_18282862',
  'variables' => 
  array (
    'file_include' => 0,
    'style_include' => 0,
    'body' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551372a3be0104_18282862')) {function content_551372a3be0104_18282862($_smarty_tpl) {?><!DOCTYPE HTML>
<html>
<head>
	<meta charset="utf-8" />
	<?php echo '<script'; ?>
 type="text/javascript" src="./js/jquery-2.0.2.min.js"><?php echo '</script'; ?>
>
	<?php echo '<script'; ?>
 type="text/javascript" src="./js/bootstrap.min.js"><?php echo '</script'; ?>
>
	<link rel="stylesheet" href="./css/bootstrap.min.css" />
	<link rel="stylesheet" href="./css/bootstrap-responsive.min.css" />

	<?php echo $_smarty_tpl->tpl_vars['file_include']->value;?>


	<style>
	body{
        padding-top: 60px; /* 60px to make the container  go all the way to the bottom of the topbar */
    }
	
	<?php echo $_smarty_tpl->tpl_vars['style_include']->value;?>


	</style>		
</head>

<body>

	<?php echo $_smarty_tpl->tpl_vars['body']->value;?>


 <div class="navbar navbar-inverse navbar-fixed-top">
	  <div class="navbar-inner">
		<div class="container">
		  <a class="brand" href="#">Project name</a>
		  <div class="nav-collapse collapse">
			<ul class="nav">
			  <li class="active"><a href="#">Home</a></li>
			  <li><a href="#about">About</a></li>
			  <li><a href="#contact">Contact</a></li>
			  <li class="dropdown">
				<a href="#" class="dropdown-toggle" data-toggle="dropdown">Dropdown <b class="caret"></b></a>
				<ul class="dropdown-menu">
				  <li><a href="#">Action</a></li>
				  <li><a href="#">other action</a></li>
				  <li><a href="#">Something else here</a></li>
				  <li class="divider"></li>
				  <li class="nav-header">Nav header</li>
				  <li><a href="#">Separated link</a></li>
				  <li><a href="#">One more separated link</a></li>
                </ul>
              </li>
            </ul>
			<form class="navbar-form pull-right" method="post">
			  <input class="input-medium" type="text" placeholder="Email">
			  <input class="input-medium" type="password" placeholder="Password">
			  <button type="submit" class="btn">登录</button>
            </form>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>
<div class="container">
  <div class="row">
	<div class="span3">
	<form class="form-inline" role="form">
	  <div class="form-group">
		<label class="sr-only" for="exampleInputEmail2">邮箱</label>
		<input type="email" class="form-control" id="exampleInputEmail2" placeholder="请输入你的邮箱地址">
	  </div>
	  <div class="form-group">
		<label class="sr-only" for="exampleInputPassword2">密码</label>
		<input type="password" class="form-control" id="exampleInputPassword2" placeholder="请输入你的邮箱密码">
	  </div>
	  <div class="checkbox">
		<label>
		  <input type="checkbox"> 记住密码
		</label>
	  </div>
	  <button type="submit" class="btn btn-default">进入邮箱</button>
	</form> 
	</div>
    <div class="span6">
	<table class="table table-striped table-bordered table-hover">
	   <thead>
		 <tr>
		   <th>表格标题</th>
		   <th>表格标题</th>
		   <th>表格标题</th>
		 </tr>
	   </thead>
	   <tbody>
		 <tr class="success">
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		 </tr>
		 <tr>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		 </tr>
		 <tr>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		 </tr>
		 <tr>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		   <td>表格单元格</td>
		 </tr>
	   </tbody>
	 </table>
  </div>
<div id="box" class="span3" style="position:relative;left:10px;top:10px;">iii</div>
</div>
</div>
<?php echo '<script'; ?>
>
console.log("aaaaaaaaa");
<?php echo '</script'; ?>
>
</body>
</html>

<?php }} ?>
