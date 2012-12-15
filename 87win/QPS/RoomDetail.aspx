<%@ Page Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="RoomDetail.aspx.cs" Inherits="QPS.Web.RoomDetail" Title="无标题页" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

<script type="text/javascript">
    function searchRoomAddress(address) {
        search(address);
    }

</script>

    <!--mid[[-->
<div class="mid">
  <div class="ssou">
               <span>
                   <asp:DataList ID="DataList2" runat="server">
                  <ItemTemplate>
                  <a ><%# Eval("Are").ToString()%></a>>
                  <a href="#">棋牌室</a>>
                  <a ><%# Eval("Name").ToString()%></a>
                  </ItemTemplate>
                   </asp:DataList>
                   </span>
          </div>
     <!--nymiddle[[-->
     <div class="nymiddle">
          <div class="jsleft">
       
              
                   <asp:DataList ID="DataList1" runat="server"  CssClass="nyleft" 
        onitemcommand="DataList1_ItemCommand" >
    <ItemTemplate>         <div class="qptopa"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
    <div class="qpmida">
               <div class="qpname">
                    <ul>
                        <li><h2><%# Eval("Name").ToString()%></h2></li>
                        <li><h3>地址：<font class="ls"><%# Eval("Address").ToString()%></font></h3></li>
                        <li><h3>价格：<font class="hs"><%# Eval("RoomPrice").ToString()%>元/小时</font></h3></li>
                        <li><h4>
                            <asp:ImageButton ID="ImageButton1"  runat="server" ImageUrl="images/nyimg2.jpg"    CommandArgument= '<%#Eval("Id") %>' CommandName="Order" /></h4>
                            <h6>
                         
                            </h6>
                            </li>
                    </ul> </div>
                          <div class="rollBox">
                                      <asp:Image ID="Image1" runat="server" ImageUrl=
                             '<%# Eval("ImagePath").ToString()%>'
                             />
                             </div>
                       </div>
                       <div class="qpenda"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
                       <div class="qpmida">
                    <div class="titleh">
                         <span>详细介绍</span>
                    </div>
                    <div class="nrjj">
					<%# Eval("Content").ToString()%>   
                    </div>
                    </div>
                    <div class="qpenda"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
               </ItemTemplate>
    </asp:DataList>
    </div>
          <div class="jsright">
                <!--
               <div class="ditu">
                    <img src="images/jsimg1.jpg" alt=""/> 
                </div>
                -->
                <div id="mapBox" class="ditu"></div>
                <input type="button" onclick="test_map()" value="test" />
          </div>
     </div>
     <!--nymiddle]]--></div>
</asp:Content>
