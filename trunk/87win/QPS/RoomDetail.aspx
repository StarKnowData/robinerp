<%@ Page Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="RoomDetail.aspx.cs" Inherits="QPS.Web.RoomDetail" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
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
     
     <div class="nymiddle">
          <div class="jsleft">
       
              
                   <asp:DataList ID="DataList1" runat="server"  CssClass="nyleft" 
        onitemcommand="DataList1_ItemCommand" >
    <ItemTemplate>         <div class="qptopa"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
    <div class="qpmida">
               <div class="qpname">
                    <ul>
                        <li><h2><%# Eval("Name").ToString()%></h2></li>
                        <li><h3>地址：<font class="ls"><span id="add"><%# Eval("Address").ToString()%></span></font></h3></li>
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
                
                <div id="mapBox" class="ditu" style="background-color:white;"></div>
                <br />
                <br />
                 <form action="#">
			        从这里出发：<input type="text" name="startPoint" id="startPoint" style="" value=""/>
			        <input type="button" onclick="getTrans();" id="getBusBtn" value="查看路线">
		        </form>
          </div>
     </div>
    </div>
    <script type="text/javascript" src="http://api.map.baidu.com/api?v=1.4"></script>
    <script type="text/javascript">
        var map;
        function $(id) {
            return document.getElementById(id);
        }

        function initMap() {
            map = new BMap.Map("mapBox");            // 创建Map实例
            var point = new BMap.Point(116.404, 39.915);    // 创建点坐标
            map.centerAndZoom(point, 15);                     // 初始化地图,设置中心点坐标和地图级别。
            map.enableScrollWheelZoom();                            //启用滚轮放大缩小 
        }

        function search() {
            var areaName = $("add").innerHTML;
            if (areaName == "") return;
            if (map == null) {
                initMap();
            }
            var local = new BMap.LocalSearch(map, {
                renderOptions: { map: map }
            });
            var searchAdd = "武汉市" + areaName;
            local.search(searchAdd);
        }

        search();

        function getTrans() {
            var areaName = $("add").innerHTML;
            if (areaName == "") return;
            var startPoint = $("startPoint").value;
            if (startPoint == "") {
                alert("请输入您当前的地址。");
                return;
            }
            var transit = new BMap.TransitRoute(map, {
                renderOptions: { map: map }
            });
            var searchAdd = "武汉市" + areaName;
            transit.search(startPoint, searchAdd);

        }
        

</script>
</asp:Content>


