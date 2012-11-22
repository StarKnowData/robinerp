<%@ Page Title="" Language="C#" MasterPageFile="~/BusiMan/EnterMaster.Master" AutoEventWireup="true" CodeBehind="RoomMan.aspx.cs" Inherits="QPS.Web.BusiMan.RoomMan" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <link href="css/gruser.css"  rel="stylesheet" type="text/css" />
    　<script type="text/javascript">
　　function openwin()
　　 {
     window.open("Room.aspx", "newwindow", "height=600, width=850, toolbar=no, menubar=no, scrollbars=no, resizable=no, location=no, status=no");
　　}
</script>

</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
             <div class="grright">
              <div class="grtitlea">
                    <span>房间管理</span>
                    <p><a href="#" onclick="openwin()">创建新的棋牌室...</a></p>
             </div>
              <div class="grbox">
                    <asp:GridView ID="gdvRoom" runat="server" CellPadding="4" 
                       ForeColor="#333333" GridLines="None"  Width="100%"
                               DataKeyNames="棋牌室编号" 
                       onrowdeleting="gdvPersonnalOrder_RowDeleting" 
                        onrowupdating="gdvRoom_RowUpdating">
                       <RowStyle BackColor="#EFF3FB" />  　 　

                       <Columns>
                                          <asp:TemplateField HeaderText="操作" ShowHeader="False" >
                   <ItemTemplate>
                   　<asp:LinkButton ID="BtnDelete" runat="server" CausesValidation="False" CommandName="Delete"
Text="删除" ForeColor="Black"  OnClientClick="return confirm('确认要删除此行信息吗？')"></asp:LinkButton>
                   </ItemTemplate></asp:TemplateField>
                             <asp:ButtonField  CommandName="Update" HeaderText="操作" Text="修改"  />
                       </Columns>
                        <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                        <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                        <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                        <HeaderStyle BackColor="#FE6A6A" Font-Bold="True" ForeColor="White" />
                        <EditRowStyle BackColor="#2461BF" />
                        <AlternatingRowStyle BackColor="White" />
    </asp:GridView></div> </div>
</asp:Content>
