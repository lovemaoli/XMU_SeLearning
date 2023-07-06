







    

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>下载文件验证</title>
    <style type="text/css">
        *{margin:0;padding:0;}
        html{height:100%;}
        body{background-color:#FFF;text-align:center;width:100%;height:100%;position : relative }
        div.download{background:url(./styles/default/image/validate_bg.jpg) no-repeat;width:412px;height:222px;border:1px solid #CCC;position:absolute;top:50%;left:50%;margin-left:-206px;margin-top:-111px;}
        fieldset{
            border:solid 0px #666;
            width:350px;
            text-align:center;
            padding-top:90px;
            margin:0 auto;
        }
        legend{
           display:none;

        }
        table.down {width:270px;margin:0 auto;border:0}
        table.down th{font:normal 13px '宋体';text-align:right;}
        table.down td{text-align:left;}
        table.down td a{font:13px/30px Arial;text-decoration:underline;color:#F87C1C;letter-spacing:1px;}
        table.down td a:hover{color:#000;}
        div.button{padding:10px;}
        input.input{border:1px solid #E4E4E4; background-color:#FFF;width:70px;height:15px;}
        input.button{font-size: 12px;
	text-decoration: none;
	letter-spacing: 5px;
    background:#F1E9D1;
	height: 18px;
	border: 1px solid #D18C0C;
	font-family: "宋体",sans-serif;
	color: #000;
    padding:2px 5px 0 5px;
    }
        </style>

</head>
<body>

<div class="download">
<fieldset>
<legend>验证码</legend>
<form action="download_validate_do.jsp" method="post">
    <input type="hidden" name="moduleType" value="1"/>
    <input type="hidden" name="fileid" value="1124333"/>
    <input type="hidden" name="resid" value="263716"/>
    <input type="hidden" name="lid" value="15789"/>
    <table cellpadding="0" cellspacing="0" class="down">
        <tr>
            <th>验证字符串:</th>
            <td>
                <div style="margin-top:-10px;height:40px;width:70px;overflow:hidden;float:left; ">
                    <iframe frameborder="0" src="./graphic_code.jsp" scrolling="no" id="graphicCode" name="graphicCode" allowtransparency="true"></iframe></div>
                   &nbsp;<a href="javascript:graphicCode.location.reload()" >刷新验证码</a>
            </td>
        </tr>
        <tr>
            <th>输入验证字符串:</th>
            <td>&nbsp;<input name="validCode" type="text" class="input" size="5"></td>
        </tr>
    </table>
    <div class="button">
        <input type="submit" value="确定" class="button">
        <input type="button" name="validate" value="关闭" class="button" onClick="window.close()">
    </div>
</form>
</fieldset>
</div>
</body>
</html>