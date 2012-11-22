<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Order.aspx.cs" Inherits="QPS.Web.BusiMan.Order" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
   <link href="css/gruser.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
    <div class="grboxa">
     <div class="grmiddle">
          <!--grright[[-->
          <div class="grright">
               <div class="grtitlea">
                    <span>修改订单</span>
               </div>
               <!--grbox[[-->
               <div class="grbox">
                    <div class="grxxa">
                    <ul>
                        <li><h3>订单编号：</h3><input type="text" name="textfield2" id="txfOrderId" class="cja1" 
                                runat="server" readonly="readonly" /></li>
                        <li><h3>棋牌室名称：</h3><input type="text" name="textfield2" id="txfRoomName" 
                                class="cja1" runat="server" readonly="readonly"/></li>
                        <li><h3>用户：</h3><input type="text" name="textfield2" id="txfUserName" class="cja1" 
                                runat="server" readonly="readonly"/></li>
                        <li><h3>酒水费用：</h3> 
                            <asp:TextBox ID="txfBeverageCost" runat="server" class="cja1" ></asp:TextBox></li>
                        <li><asp:Button ID="btnCreate" runat="server" Text="修改" onclick="btnCreate_Click" class="cjaaa"/></li>
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