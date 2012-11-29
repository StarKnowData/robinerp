<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Trans_TransSeach" Codebehind="TransSeach.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
            <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
    <form id="form1" action="Trans.aspx?act=post" method="get">
    <input type="hidden" id="act" name="act" value ="post" />
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="11">
                    <font color="red"><strong>转账记录搜索</strong></font></td>
            </tr>
            <tr>
                <td align="right">
                    <strong>注意时项：</strong></td>
                <td align="left">
                    <strong>在记录很多的情况下搜索条件越多查询越慢，请尽量减少查询条件。</strong></td>
            </tr>
           <!-- <tr>
                <td align="right">
                    <span class="STYLE1">*</span>最多显示记录数：</td>
                <td align="left">
                    <input name="rr" type="text" id="rr" value="0" class="put" />
                    （为0代表全部）</td>
            </tr>-->
            <tr>
                <td width="17%" align="right">
                    转账人：</td>
                <td width="83%" align="left">
                    <input name="zz" type="text" id="zz" class="put" />
                    （需要输入完整的用户名）</td>
            </tr>
            <tr>
                <td align="right">
                    接受人：</td>
                <td align="left">
                    <input name="jj" type="text" id="jj" class="put" />
                    （需要输入完整的用户名）</td>
            </tr>
            <tr style="display:none">
                <td align="right" >
                    划账IP地址：</td>
                <td align="left">
                    <input name="ii" type="text" id="ii" class="put" maxlength="15" />
                    （格式为：127.0.0.1）</td>
            </tr>
            <tr style="display:none;">
                <td align="right">
                    划帐人ID：</td>
                <td align="left">
                    <input name="hd" type="text" id="hd" class="put" />
                    </td>
            </tr>
            <tr style="display:none;">
                <td align="right" >
                    接受人ID：</td>
                <td align="left">
                    <input name="zd" type="text" id="zd" class="put" maxlength="15" />
                    </td>
            </tr>
            <tr>
                <td align="right">
                    <span class="STYLE1">*</span>划账时间：</td>
                <td align="left">
                    <input name="t1" type="text" id="t1" value="0" size="6" maxlength="10" class="put" />
                    小时前到
                    <input name="t2" type="text" id="t2" value="0" size="6" maxlength="10" class="put" />
                    小时前（前面输入的数比后面的数小，0,0表示，没有时间限制）
                </td>
            </tr>
            <tr>
                <td colspan="2" align="left" bgcolor="#99cccc">
                    <strong>特殊查询（注意： &lt;多于&gt; 或 &lt;少于&gt; 已默认包含 &lt;等于&gt;；条件留空则不使用此条件） </strong>
                </td>
            </tr>
            <tr>
                <td align="right">
                    <span class="STYLE1">*</span>划账金币数：</td>
                <td align="left">
                    <input name="mr" type="radio" value="1" checked="checked" class="put" />
                    多于
                    <input type="radio" name="mr" value="0" Class="put"/>
                    少于
                    <input name="mm" type="text" id="mm" value="0" size="15" maxlength="20" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    <span class="STYLE1">*</span>手续费：</td>
                <td align="left">
                    <input name="sr" type="radio" value="1" checked="checked" class="put" />
                    多于
                    <input type="radio" name="sr" value="0" class="put" />
                    少于
                    <input name="ss" type="text" id="ss" value="0" size="15" maxlength="20" class="put" /></td>
            </tr>
            <tr>
                <td align="right">
                    <input type="hidden" name="action" value="search" /></td>
                <td align="left">
                    <input type="submit" name="Submit" value=" 查 询 " class="put" /></td>
            </tr>
        </table>
    </form>
</body>
</html>
