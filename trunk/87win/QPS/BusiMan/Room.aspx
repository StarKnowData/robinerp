<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Room.aspx.cs" Inherits="QPS.Web.BusiMan.Room" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <script type="text/javascript">

    </script>
    <link href="css/gruser.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
    <div class="grboxa">
     <div class="grmiddle">
          <!--grright[[-->
          <div class="grright">
               <div class="grtitlea">
                    <span>创建房间</span>
               </div>
               <!--grbox[[-->
               <div class="grbox">
                    <div class="grxxa">
                    <ul>
                        <li><h3>棋牌室名：</h3><input type="text" name="textfield2" id="txfName" class="cja1" runat="server" /></li>
                        <li><h3>棋牌室类型：</h3>
                            <asp:DropDownList ID="txfRoomType" CssClass="cja1" runat="server">
                                <asp:ListItem>标准</asp:ListItem>
                                <asp:ListItem>豪华</asp:ListItem>
                            </asp:DropDownList>
                            </li>
                        <li><h3>棋牌室价格：</h3><input type="text" name="textfield2" id="txfRoomPrice" class="cja1" runat="server"/></li>
                        <li><h3>地区：</h3>
                            <asp:DropDownList ID="txfArea" CssClass="cja1" runat="server">
                                <asp:ListItem>江岸区</asp:ListItem>
                                <asp:ListItem>江汉区</asp:ListItem>
                                <asp:ListItem>硚口区</asp:ListItem>
                                <asp:ListItem>汉阳区</asp:ListItem>
                                <asp:ListItem>武昌区</asp:ListItem>
                                <asp:ListItem>青山区</asp:ListItem>
                                <asp:ListItem>洪山区</asp:ListItem>
                                <asp:ListItem>东西湖区</asp:ListItem>
                                <asp:ListItem>汉南区</asp:ListItem>
                                <asp:ListItem>蔡甸区</asp:ListItem>
                                <asp:ListItem>江夏区</asp:ListItem>
                                <asp:ListItem>黄陂区</asp:ListItem>
                                <asp:ListItem>新洲区</asp:ListItem>
                            </asp:DropDownList>
                            </li>
                         <li><h3>地址：</h3><input type="text" name="textfield2" id="txfAddress" class="cja1" runat="server"/></li>
                              <li><h3>图片：</h3>
                                  <asp:FileUpload ID="fulImg" runat="server"  cssClass="cja1" /></li>
                            <li><h3>内容：</h3><input type="text" name="textfield2" id="txfContent" class="cja1" runat="server"/></li>
                        <li>
                              <asp:Button ID="btnCreate" runat="server" Text="创建" onclick="btnCreate_Click" class="cjaaa"/></li>
                    </ul>
                        
               </div>
               </div>
               <!--grbox]]-->
          </div>
          <!--grright]]-->
     </div>
     </div>
    </form>
</body>
</html>
