<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="RoomOrder.aspx.cs" Inherits="QPS.Web.RoomOrder" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <script type="text/javascript">

function showElement(elementId)
{
  document.getElementById(elementId).style.display="block";
}
function hideElement(elementId)
{
  document.getElementById(elementId).style.display="none";
}

    function addFavorite() {
        var thisURL = document.URL;
        var favURL = "http://" + getHost(thisURL);
        if (document.all) {
            window.external.addFavorite(favURL, "网站名称");
        } else {
            window.sidebar.addPanel('网站名称', favURL, "");
        }
        return false;
    }
    function SetHome(obj) {
        var vrl = "http://" + getHost(document.URL);
        try {
            obj.style.behavior = 'url(#default#homepage)'; obj.setHomePage(vrl);
        }
        catch (e) {
            if (window.netscape) {
                try {
                    netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
                }
                catch (e) {
                    alert("此操作被浏览器拒绝！\n请在浏览器地址栏输入“about:config”并回车\n然后将[signed.applets.codebase_principal_support]设置为'true'");
                }
                var prefs = Components.classes['@@mozilla.org/preferences-service;1'].getService(Components.interfaces.nsIPrefBranch);
                prefs.setCharPref('browser.startup.homepage', vrl);
            }
        }
    }

    var getHost = function(url) {
        var host = "null";
        if (typeof url == "undefined" || null == url)
            url = window.location.href;
        var regex = /.*\:\/\/([^\/]*).*/;
        var match = url.match(regex);
        if (typeof match != "undefined" && null != match)
            host = match[1];
        return host;
    }

　　
    //得到焦点时触发事件
    function onFocusFun(element, elementValue) {
        if (element.value == elementValue) {
            element.value = "";
            element.style.color = "";
        }
    }
    //离开输入框时触发事件
    function onblurFun(element, elementValue) {
        if (element.value == '') {
            element.style.color = "#808080";
            element.value = elementValue;
        }
    }
        </script>
<div class="middlea">
     <div class="mid">
          <div class="qptop"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="qpmid">
               <div class="diqu">
                    <ul><h3>区域：</h3>
                    <h4>
                    <a ><asp:LinkButton ID="lbtall1" runat="server" Text="全部" 
                           onclick="allone_Click"></asp:LinkButton></a>
                    </h4>
                    <h5> <asp:DataList ID="DataList2" runat="server" BorderWidth="0px" 
                        RepeatDirection="Horizontal"  
                  onitemcommand="DataList2_ItemCommand">
                    <HeaderTemplate></HeaderTemplate>
                   <ItemTemplate >
                   
                       <asp:LinkButton ID="lbtAre" runat="server"  CommandArgument=' <%#Eval("Are") %>' CommandName="order" > <%# Eval("Are").ToString()%> (<%# Eval("Sum").ToString()%>)</asp:LinkButton>
                   </ItemTemplate>
                   <FooterTemplate>
                   </FooterTemplate>
              </asp:DataList></h5></ul>
                    <ul><h3>价格：</h3>
                    <h4><a ><asp:LinkButton ID="lbtall2" runat="server" Text="全部" 
                           onclick="alltwo_Click"></asp:LinkButton></a></h4>
                    <h5>
                  <a ><asp:LinkButton ID="lbt2050" runat="server" Text="20-50元" 
                           onclick="lbt2050_Click"></asp:LinkButton></a>   <a >
                       <asp:LinkButton ID="lbt50100" runat="server" Text="50-100元" 
                           onclick="lbt50100_Click"></asp:LinkButton></a>
                  <a>
                       <asp:LinkButton ID="lbt100200" runat="server" Text="100-200元" 
                           onclick="lbt100200_Click"></asp:LinkButton></a>
                  <a >
                       <asp:LinkButton ID="lbt200300" runat="server" Text="200-300元" onclick="lbt200300_Click"></asp:LinkButton></a>
               <a >
                       <asp:LinkButton ID="lbt300" runat="server" Text="300元以上" onclick="lbt300_Click"></asp:LinkButton></a></h5></ul>
                       <ul><a><asp:TextBox ID="textfield" class="texta1" Text="请输入地址或名称" runat="server" OnFocus="onFocusFun(this,'请输入地址或名称查询')"
　　OnBlur="onblurFun(this,'请输入地址或名称查询')"></asp:TextBox></a>
                  <a><asp:Button ID="Button1" runat="server" Text="" class="texta2" 
                      onclick="ButSearch_Click"/></a></ul>
                    <ul class="l"><h3>排序：</h3><span><a>
                           <asp:LinkButton ID="LinkButton1" runat="server" Text="默认"  onclick="LinkButton1_Click"></asp:LinkButton></a></span>
                     <span> <a ><asp:LinkButton ID="lbtPriceOrder" runat="server" Text="价格"  onclick="lbtPriceOrder_Click"></asp:LinkButton></a></span>
                      </ul>
               </div>
          </div>
          <div class="qpend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="qptop"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="qpmid">
               <div class="qpbox">
                    <asp:DataList ID="DataList1" runat="server" BorderWidth="0px" 
                        RepeatDirection="Horizontal" RepeatColumns="3" Width="1000px" 
                  onitemcommand="DataList1_ItemCommand">
                    <HeaderTemplate></HeaderTemplate>
                   <ItemTemplate >
                   <div class="qplist">
                     <div class="qpnra">
                          <a>
                          <asp:Image ID="Image1" runat="server" ImageUrl=
                             '<% # Eval("ImagePath")%>'
                             /></a>
                         <h3>
                         <a ><%# Eval("Address")%></a>
                         <a><%# Eval("Name")%></a>
                         </h3><div style="clear:both; overflow:hidden; height:0; font-size:1px"></div>
                         <h4><%# GetSubString(Convert.ToString(Eval("Content")), 130) %></h4>
                    </div>
                    <div class="qpjg">
                         <ul>
                             <h3><a >现价￥<%# Eval("RoomPrice")%></a></h3>
                         </ul>
                         <a>
                             <asp:ImageButton ID="ImageButton1" runat="server" 
                             ImageUrl="images/img5.jpg" 
                             CommandArgument=' <%#Eval("Id")  %>' CommandName="ShowDetail"/></a>
                      </div>
                      </div>
                   </ItemTemplate>
                   <FooterTemplate>
                   </FooterTemplate>
              </asp:DataList>
               </div>
               <div class="page">
                <asp:Label ID="Label1" runat="server" CssClass="lbl" Text="第"></asp:Label>
                <asp:Label ID="lblcurrent" runat="server" CssClass="lbl" Text="1"></asp:Label>
                <asp:Label ID="Label3" runat="server" CssClass="lbl" Text="页  共"></asp:Label>
                <asp:Label ID="lblall" runat="server" CssClass="lbl" Text="10"></asp:Label>
                <asp:Label ID="Label5" runat="server" CssClass="lbl" Text="页  "></asp:Label>
                <asp:LinkButton ID="lblfirst" runat="server" CssClass="n" 
                    onclick="lblfirst_Click" >首页</asp:LinkButton>
                <asp:LinkButton ID="lbtnform" runat="server" Class="n" onclick="lbtnform_Click">上一页</asp:LinkButton>
                <asp:LinkButton ID="lbtnnext" runat="server" CssClass="n" onclick="lbtnnext_Click">下一页</asp:LinkButton>
                <asp:LinkButton ID="lbllast" runat="server" CssClass="n" 
                    onclick="lbllast_Click" >尾页</asp:LinkButton>
                <asp:TextBox ID="txtnum" runat="server" CssClass="txt"></asp:TextBox>
                <asp:Button ID="btngo" runat="server" CssClass="go" Text="前往" 
                    onclick="btngo_Click" />
            </div>
          </div>
          <div class="qpend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
     </div>
</div>
<!--middlea]]-->
    </span>
</asp:Content>
