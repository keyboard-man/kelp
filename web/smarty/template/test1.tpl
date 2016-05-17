<!DOCTYPE HTML>
<html>
<head>
	<meta charset="utf-8" />
	<script type="text/javascript" src="./js/jquery-2.0.2.min.js"></script>
	<script type="text/javascript" src="./js/bootstrap.min.js"></script>
	<link rel="stylesheet" href="./css/bootstrap.min.css" />
	<link rel="stylesheet" href="./css/bootstrap-responsive.min.css" />

	{$file_include}

	<style>
	body{
        padding-top: 60px; /* 60px to make the container  go all the way to the bottom of the topbar */
    }
	
	{$style_include}

	</style>		
</head>

<body>

	{$body}

 <div class="navbar navbar-inverse navbar-fixed-top">
	  <div class="navbar-inner">
		<div class="container">
		  <a class="brand" href="#">Kelp</a>
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
<script>
console.log("aaaaaaaaa");
</script>
</body>
</html>

