<%@ Page Language="C#" ContentType="text/html" AspCompat="true" %> <%--SmartNavigation="True" --%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>ASPX网站探针 - V1.0</title>
    <style type="text/css">
        <!--
        a:link{ color: #000000; text-transform: #000000; text-decoration: none }
        a:visited { color: #000000; text-transform: #000000; text-decoration: none }
        a:active { color: #3333ff; font-style: normal; text-decoration: none }
        a:hover { color: red; font-style: normal; text-decoration: underline; font-weight: normal}
        font{font-size: 14px;}
        td{font-size: 14px;}
        body{font-size: 14px;}
        .fontColor1 {color: #CC6600}
        .fontBig1 {font-size: 14px}
        .fonts {	COLOR: #3F8805
        }
        .backq {	BACKGROUND-COLOR: #eefee0
        }
        .backs {	COLOR: #ffffff; BACKGROUND-COLOR: #3f8805
        }
        .fonts1 {	COLOR: #3f8805
        }
        .backc {	BACKGROUND-COLOR: #3F8805;
	        BORDER: medium none;
	        COLOR: #ffffff;
	        HEIGHT: 18px;
	        font-size: 9pt
        }
        .backq1 {	BACKGROUND-COLOR: #EEFEE0
        }
        .input {	BORDER: #111111 1px solid;
	        FONT-SIZE: 9pt;
	        BACKGROUND-color: #F8FFF0
        }
        .backs1 {	BACKGROUND-COLOR: #3F8805;
	        COLOR: #ffffff;
        }
        .run{color: red;}
        -->
    </style>
    
    <script type="text/javascript">
        function GetNowTime(){
            var day="";
            var month="";
            var ampm="";
            var ampmhour="";
            var myweekday="";
            var year="";
            mydate=new Date();
            myweekday=mydate.getDay();
            mymonth=mydate.getMonth()+1;
            myday= mydate.getDate();
            myyear= mydate.getYear();
            year=(myyear > 200) ? myyear : 1900 + myyear;
            if(myweekday == 0)
            weekday=" 星期日 ";
            else if(myweekday == 1)
            weekday=" 星期一 ";
            else if(myweekday == 2)
            weekday=" 星期二 ";
            else if(myweekday == 3)
            weekday=" 星期三 ";
            else if(myweekday == 4)
            weekday=" 星期四 ";
            else if(myweekday == 5)
            weekday=" 星期五 ";
            else if(myweekday == 6)
            weekday=" 星期六 ";
            document.write(year+"年"+mymonth+"月"+myday+"日 "+weekday);
        }
    </script>
</head>
<body link="#FF6600" vlink="#FF6600" alink="#FF6600">
    <form id="Form1" runat="server">
        <table width="556" border="0" align="center" cellpadding="0" cellspacing="0">
            <tr>
                <td>
                    <div align="center" class="fontBig1">
                        <div align="center">
                            <strong>您好，今天是<script language="JavaScript" type="text/JavaScript">GetNowTime();</script></strong></div>
                    </div>
                    <div align="left">
                        <br>
                        <br>
                    </div>
                    <div class="fontColor1">
                        是否支持.NET平台</div>
                    <br>
                    出现以下情况即说明您的空间不支持ASPX文件：<br>
                    1、访问本文件时提示下载。
                    <br>
                    2、访问本文件时看到类似@#&lt;&gt;等字符。
                    <p>
                        <font class="fonts1">服务器的基本参数</font>
                    </p>
                    <table cellspacing="0" cellpadding="0" width="500" bgcolor="#3f8805" border="0">
                        <tbody>
                            <tr>
                                <td>
                                    <table cellspacing="1" cellpadding="0" width="500" border="0">
                                        <tbody>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td width="135" align="left">
                                                    &nbsp;服务器名</td>
                                                <td width="312">
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="name" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器IP</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="ip" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器域名</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="domain" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器端口</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="port" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器时间</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="ontime" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器语言</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="lan" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器CPU数量</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="cpuqty" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器CPU结构</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="cpumore" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;服务器操作系统</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="system" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;DotNET引擎版本<font size="2">&nbsp;</font></td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="dotnet" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                        </tbody>
                                    </table>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <p>
                        <font class="fonts1">服务器的其它参数</font>
                    </p>
                    <table cellspacing="0" cellpadding="0" width="500" bgcolor="#3f8805" border="0">
                        <tbody>
                            <tr>
                                <td>
                                    <table cellspacing="1" cellpadding="0" width="500" border="0">
                                        <tbody>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td width="135" align="left">
                                                    &nbsp;当前执行用户</td>
                                                <td width="312">
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="user" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;系统安装目录
                                                </td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="sysdir" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;系统临时目录</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="systmp" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;IIS版本</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="IIS" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;SSL支持</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="SSL" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;CGI版本</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="CGI" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;脚本超时时间</td>
                                                <td bgcolor="#eefee0">
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="timeout" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;系统运行时间</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="runtime" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;当前文件目录</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="path" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;当前文件位置</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="pathinfo" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;已使用内存</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="mem" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                            <tr bgcolor="#eefee0" height="18">
                                                <td align="left">
                                                    &nbsp;主机所在域</td>
                                                <td>
                                                    <font size="2">&nbsp;
                                                        <asp:Label ID="atdomain" runat="server" />
                                                    </font>
                                                </td>
                                            </tr>
                                        </tbody>
                                    </table>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    <font class="fonts1">组件支持情况</font><br>
                    * IIS自带的常用组件
                    <table style="border-collapse: collapse" bordercolor="#3f8805" cellspacing="0" cellpadding="0"
                        width="500" border="1">
                        <tbody>
                            <tr class="backs" align="middle" height="18">
                                <td width="325">
                                    组 件 名 称</td>
                                <td width="37" align="center">
                                    支持</td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.AdRotator<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="adrot" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.BrowserType<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="brow" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.NextLink<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="next" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.Tools<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="tool" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.Status<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="stat" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.Counters<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="coun" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;IISSample.ContentRotator<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    &nbsp;<font class="fonts1"><b><font size="2">
                                        <asp:Label ID="cont" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;IISSample.PageCounter<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="pagec" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;MSWC.PermissionChecker<font color="#888888">&nbsp;</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="perm" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;Scripting.FileSystemObject<font color="#888888">&nbsp;(FSO 文本文件读写)</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="fso" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;Adodb.Connection<font color="#888888">&nbsp;(ADO 数据对象)</font></td>
                                <td align="left">
                                    <font class="fonts1"><b>&nbsp;<font color="red"><b></b></font><font size="2">
                                        <asp:Label ID="adodb" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    * 常见的文件上传组件
                    <table style="border-collapse: collapse" bordercolor="#3f8805" cellspacing="0" cellpadding="0"
                        width="500" border="1">
                        <tbody>
                            <tr class="backs" align="middle" height="18">
                                <td width="324">
                                    组 件 名 称</td>
                                <td width="40" align="center">
                                    支持</td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;SoftArtisans.FileUp<font color="#888888">&nbsp;(SA-FileUp 文件上传)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="saup" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;SoftArtisans.FileManager<font color="#888888">&nbsp;(SoftArtisans 文件管理)</font></td>
                                <td align="left">
                                    <font class="fonts1"><b><font size="2"></font><font color="red"><b>&nbsp;<font class="fonts1"><b><font
                                        size="2"> </font></b></font></b></font><font size="2">
                                            <asp:Label ID="arup" runat="server" />
                                        </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;LyfUpload.UploadFile<font color="#888888">&nbsp;(刘云峰的文件上传组件)</font></td>
                                <td align="left">
                                    &nbsp;<font class="fonts1"><b><font size="2">
                                        <asp:Label ID="lyup" runat="server" />
                                    </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;Persits.Upload.1<font color="#888888">&nbsp;(ASPUpload 文件上传)</font></td>
                                <td align="left">
                                    <font class="fonts1"><b><font size="2"></font><font color="red"><b>&nbsp;<font class="fonts1"><b><font
                                        size="2"> </font></b></font></b></font><font size="2">
                                            <asp:Label ID="aspup" runat="server" />
                                        </font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;w3.upload<font color="#888888">&nbsp;(Dimac 文件上传)</font></td>
                                <td align="left">
                                    <font class="fonts1"><b><font size="2"></font><font color="red"><b>&nbsp;<font class="fonts1"><b><font
                                        size="2"> </font></b></font></b></font><font size="2">
                                            <asp:Label ID="w3up" runat="server" />
                                        </font></b></font>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    * 常见的邮件收发组件
                    <table style="border-collapse: collapse" bordercolor="#3f8805" cellspacing="0" cellpadding="0"
                        width="500" border="1">
                        <tbody>
                            <tr class="backs" align="middle" height="18">
                                <td width="323">
                                    组 件 名 称</td>
                                <td width="40" align="center">
                                    支持</td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;JMail.SmtpMail<font color="#888888">&nbsp;(Dimac JMail 邮件收发) </font>
                                </td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="jmail" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;CDONTS.NewMail<font color="#888888">&nbsp;(虚拟 SMTP 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="cdon" runat="server" />
                                        </font></b></font></b></font>&nbsp;<font color="red">&nbsp;</font></td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;Persits.MailSender<font color="#888888">&nbsp;(ASPemail 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="pers" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;SMTPsvg.Mailer<font color="#888888">&nbsp;(ASPmail 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="smtp" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;DkQmail.Qmail<font color="#888888">&nbsp;(dkQmail 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="qmail" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;Geocel.Mailer<font color="#888888">&nbsp;(Geocel 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="mailer" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;IISmail.Iismail.1<font color="#888888">&nbsp;(IISmail 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="iismail" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;SmtpMail.SmtpMail.1<font color="#888888">&nbsp;(SmtpMail 发信)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="smtpmail" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    * 常见的图像处理组件
                    <table style="border-collapse: collapse" bordercolor="#3f8805" cellspacing="0" cellpadding="0"
                        width="500" border="1">
                        <tbody>
                            <tr class="backs" align="center" height="18">
                                <td width="372">
                                    组 件 名 称</td>
                                <td width="122" align="center">
                                    支持</td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;SoftArtisans.ImageGen<font color="#888888">&nbsp;(SA 的图像读写组件)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="saimg" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;W3Image.Image<font color="#888888">&nbsp;(Dimac 的图像读写组件)</font></td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="w3img" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                    <br>
                    * 其他组件支持情况检测<br>
                    <table border="1" cellpadding="0" cellspacing="0" style="border-collapse: collapse"
                        bordercolor="#3F8805" width="500">
                        <tr height="18" class="backq1">
                            <td height="30">
                                输入组件的ProgId或ClassId
                                <asp:TextBox ID="classname" Rows="1" runat="server" TextMode="SingleLine" />
                                <asp:Button ID="classsub" runat="server" Text="检测" OnClick="sub" />
                            </td>
                        </tr>
                    </table>
                    <div align="center">
                        <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                            <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                <asp:Label ID="classinfo" runat="server" />
                            </font></b></font></b></font>
                    </div>
                    <p class="fonts">
                        服务器性能测试</p>
                    <table style="border-collapse: collapse" bordercolor="#3f8805" cellspacing="0" cellpadding="0"
                        width="500" border="1">
                        <tbody>
                            <tr class="backs" align="middle" height="18">
                                <td width="298">
                                    测试项目</td>
                                <td width="78" align="center">
                                    使用时间</td>
                                <td width="76">
                                    &nbsp;</td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;本页执行时间:打开本页面的速度测试</td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="timerun" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                                <td align="left">
                                    &nbsp;<font color="red"><a href="Serverinfo.aspx" class="run">重算</a></font></td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;整数运算测试:进行100万次加法运算</td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="timetol" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                                <td align="left">
                                    &nbsp;<font color="red"><a href="Serverinfo.aspx" class="run">重算</a> </font>
                                </td>
                            </tr>
                            <tr class="backq" height="18">
                                <td align="left">
                                    &nbsp;浮点运算测试:进行100万次开方运算</td>
                                <td align="left">
                                    <font color="red"><b>&nbsp;<font class="fonts1"><b><font size="2"> </font><font color="red">
                                        <b><font class="fonts1"><b><font size="2"></font></b></font></b></font><font size="2">
                                            <asp:Label ID="timekai" runat="server" />
                                        </font></b></font></b></font>
                                </td>
                                <td align="left">
                                    <font color="red">&nbsp;<a href="Serverinfo.aspx">重算</a></font></td>
                            </tr>
                        </tbody>
                    </table>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>

<script language="C#" runat="server">
    public void Page_Load(Object sender, EventArgs e)
    {
        Response.Expires = 0;
        Response.CacheControl = "no-cache";
        if (!Page.IsPostBack)
        {
            //取得页面执行开始时间
            DateTime stime = DateTime.Now;

            int build, major, minor, revision;
            build = Environment.Version.Build;
            major = Environment.Version.Major;
            minor = Environment.Version.Minor;
            revision = Environment.Version.Revision;

            name.Text = Server.MachineName;
            ip.Text = Request.ServerVariables["LOCAL_ADDR"];
            domain.Text = Request.ServerVariables["SERVER_NAME"];
            port.Text = Request.ServerVariables["SERVER_PORT"];
            ontime.Text = DateTime.Now.ToString();
            lan.Text = Request.ServerVariables["HTTP_ACCEPT_LANGUAGE"];
            cpuqty.Text = System.Environment.GetEnvironmentVariable("NUMBER_OF_PROCESSORS");
            cpumore.Text = System.Environment.GetEnvironmentVariable("PROCESSOR_ARCHITECTURE");
            system.Text = Environment.OSVersion.ToString();
            dotnet.Text = ".NET CLR  " + major + "." + minor + "." + build + "." + revision;

            user.Text = Environment.UserName;
            sysdir.Text = System.Environment.GetEnvironmentVariable("windir");
            systmp.Text = System.Environment.GetEnvironmentVariable("TEMP");
            mem.Text = (Environment.WorkingSet / 1024 / 1024).ToString() + " MB";
            atdomain.Text = System.Environment.GetEnvironmentVariable("USERDOMAIN");


            SSL.Text = Request.ServerVariables["HTTPS"];
            CGI.Text = Request.ServerVariables["GATEWAY_INTERFACE"];
            IIS.Text = Request.ServerVariables["SERVER_SOFTWARE"];
            timeout.Text = Server.ScriptTimeout.ToString();
            runtime.Text = Math.Round((decimal)(Environment.TickCount / 600 / 60)) / 100 + " 小时";
            path.Text = Request.ServerVariables["APPL_PHYSICAL_PATH"];
            pathinfo.Text = Request.ServerVariables["PATH_TRANSLATED"];


            //组件支持验证代码
            this.check("MSWC.AdRotator", adrot);
            this.check("MSWC.BrowserType", brow);
            this.check("MSWC.NextLink", next);
            this.check("MSWC.Tools", tool);
            this.check("AMSWC.Status", stat);
            this.check("MSWC.Counters", coun);
            this.check("IISSample.ContentRotator", cont);
            this.check("IISSample.PageCounter", pagec);
            this.check("MSWC.PermissionChecker", perm);
            this.check("Scripting.FileSystemObject", fso);
            this.check("ADODB.RecordSet", adodb);

            this.check("SoftArtisans.FileUp", saup);
            this.check("SoftArtisans.FileManager", arup);
            this.check("LyfUpload.UploadFile", lyup);
            this.check("Persits.Upload", aspup);
            this.check("W3.Upload", w3up);

            this.check("JMail.SMTPMail", jmail);
            this.check("CDONTS.NewMail", cdon);
            this.check("Persits.MailSender", pers);
            this.check("SMTPsvg.Mailer", smtp);
            this.check("dkQmail.Qmail", qmail);
            this.check("Geocel.Mailer", mailer);
            this.check("iismail.iismail.1", iismail);
            this.check("SmtpMail.SmtpMail.1", smtpmail);

            this.check("SoftArtisans.ImageGen", saimg);
            this.check("W3Image.Image", w3img);


            //取得页面执行结束时间
            DateTime etime = DateTime.Now;
            //计算页面执行时间
            timerun.Text = ((etime - stime).TotalMilliseconds).ToString() + "毫秒";

            //100万次相加循环测试
            DateTime ontime1 = DateTime.Now;
            int sum = 0;
            for (int i = 1; i <= 10000000; i++)
            {
                sum = sum + i;
            }
            DateTime endtime1 = DateTime.Now;
            timetol.Text = ((endtime1 - ontime1).TotalMilliseconds).ToString() + "毫秒";

            //100万次开平方测试
            DateTime ontime2 = DateTime.Now;
            long k = 2;
            for (int a = 1; a < 1000000; a++)
            {
                k = k * k;
            }
            DateTime endtime2 = DateTime.Now;
            timekai.Text = ((endtime2 - ontime2).TotalMilliseconds).ToString() + "毫秒";


        }
    }
    
    bool isobj(string obj)
    {
        try
        {
            object meobj = Server.CreateObject(obj);
            return (true);
        }
        catch
        {
            return (false);
        }
    }

    void check(string obj, Label sup)
    {
        string yes = "<font class=fonts1><b>√</b></font>";
        string no = "<font color=red><b>×</b></font>";
        try
        {
            object claobj = Server.CreateObject(obj);
            sup.Text = yes;
        }
        catch
        {
            sup.Text = no;
        }
    }

    //自定义组件查询
    public void sub(Object Sender, EventArgs e)
    {
        string classobj = classname.Text;
        if (isobj(classobj))
        {
            classinfo.Text = "检测结果：支持组件" + classobj;
        }
        else
        {
            classinfo.Text = "检测结果：不支持组件" + classobj;
        }
    }

</script>