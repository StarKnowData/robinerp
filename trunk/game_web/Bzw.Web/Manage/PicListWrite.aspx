<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PicListWrite" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/public/js/public.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    上传照片</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 上传照片</p>
            </div>
            <div id="sub_nr" style="margin-top: 15px;">
                <div class="frie_pro">
                    <a href="Album.aspx" id="current">
                        <img src="/images/fhphoto.gif" width="12" height="12" />
                        返回相册列表</a> &nbsp;&nbsp;| &nbsp;&nbsp;<a href="PicListWrite.aspx"><img src="/images/scphoto.gif"
                            width="12" height="12" />
                            上传相片</a>
                </div>
                <form action="/Manage/UsersForm.aspx?params=addpic<%=pic==null?"":"&id="+pic.ID.ToString()%>"
                method="post" onsubmit="return OnFormSubmit();" enctype="multipart/form-data" class="democss">
                <div class="cz">
                    <table width="100%" border="0" class="tab07"  style="border-top:0px;">
                        <tr>
                            <td height="30" align="right" valign="middle">
                                &nbsp;
                            </td>
                            <td>
                                &nbsp;
                            </td>
                        </tr>
                        <tr>
                            <td width="21%" height="30" align="right" valign="middle">
                                选择相册：
                            </td>
                            <td width="79%">
                                <span class="fr_news">
                                    <select id="selColumnId" name="selColumnId">
                                        <% if (ColumnList.Rows.Count > 0)
                                           {
                                               foreach (System.Data.DataRow row in ColumnList.Rows)
                                               {
                                        %>
                                        <option value="<%=row[Bzw.Entities.Web_UserAlbumColumn._.ID.Name] %>">
                                            <%=row[Bzw.Entities.Web_UserAlbumColumn._.AlbumName.Name].ToString() %>
                                        </option>
                                        <%
                                            }
              } %>
                                    </select>
                                </span>
                            </td>
                        </tr>
                        <tr>
                            <td height="30" align="right" valign="middle">
                                照片名称：
                            </td>
                            <td>
                                <input type="text" id="txtPicName" name="txtPicName" value="<%=pic==null? "" : pic.PicName %>"
                                    class="pro_input" maxlength="15" />
                            </td>
                        </tr>
                        <tr>
                            <td height="30" align="right" valign="middle">
                                选择照片：
                            </td>
                            <td>
                                <% if (pic == null || string.IsNullOrEmpty(pic.PicPath))
                                   { %>
                                <input type="file" id="filePicPath" name="filePicPath" /><br />
                                <span style="color: Red;">允许的图片大小：100K以内，允许的图片类型：jpg，jpeg，gif，bmp，png</span>
                                <%}
                                   else
                                   {
                                %>

                                <script>var pcid = <%=pic.ColumnID %>;</script>

                                <input type="text" value="<%=pic.PicPath %>" readonly="readonly" />&nbsp;&nbsp;<input
                                    type="button" value="查看" onclick="OpenUrl('<%=pic.PicPath %>');" />&nbsp;&nbsp;<input
                                        type="button" value="删除" onclick="DelPic(<%=pic.ID %>);" />
                                <%
                                    }%>
                            </td>
                        </tr>
                        <tr>
                            <td align="right" valign="middle">
                                照片描述：
                            </td>
                            <td>
                                <textarea cols="35" rows="5" id="txtPicDescription" name="txtPicDescription"><%=pic == null ? "" : pic.PicDescription %></textarea>
                            </td>
                        </tr>
                        <tr>
                            <td height="53">
                                &nbsp;
                            </td>
                            <td align="left" valign="bottom">
                                <input type="submit" name="button5" class="but_011" id="button5" value="<%=(pic == null) ? "上传照片" : "修改相册" %>" />&nbsp;<input
                                    type="button" name="button5" class="but_back" id="Submit1" value="  " onclick="javascript:history.back();" />
                            </td>
                        </tr>
                        <tr>
                            <td height="22" colspan="2">
                                &nbsp;
                            </td>
                        </tr>
                    </table>
                </div>
                </form>
            </div>    <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <div class="clear">
    </div>
   
     
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />

    <script>
        function OnFormSubmit() {
            var ck = new CK_HtmlControl();
            ck.Postfix = "</li>";
            if (ck.Required_TextBox($("#txtPicName")[0], "<li style='color:red;'>-相片名称", 50, 2)) {
                return true;
            }
            else {
                var error = '<strong>您的输入有以下错误：</strong><br /><ol>';
                error += ck.Message + "</ol>";
                Msg(ERROR_MSG_ICON + error, 300);
                return false;
            }
        }

        if (typeof pcid != "undefined" && pcid != null && pcid != "" && pcid != 0) {
            DropSetByValue("selColumnId", pcid);
        }

        function DelPic(id) {
            if (!confirm("您确定要删除这张相片吗？\r\n注意：此操作不可恢复！"))
                return;
            OpenStateBar("正在删除，请稍候...");
            $.get(
					"/Manage/UsersForm.aspx?params=delpic&type=0&id=" + id + "&x=" + Math.random(),
					function(data) {
					    if (data == "success") {
					        LocationTo(location.href);
					    }
					    else {
					        Msg(data, 200);
					    }
					}
				);
        }
    </script>

</body>
</html>
