<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="WebQQ.ascx.cs" Inherits="Bzw.Web.Public.WebQQ" %>
<div id="qq" style="z-index: 3;">
    <div class="fl" id="qqfl" style="display:block;left:0px;">
        <h2 style="background: url('/Images/qq/pop_tit01.png') no-repeat; width: 130px; height: 46px;">
            <span id="qqcls" style="width: 25px; height: 25px; top: 0; cursor: pointer; float: right;">
            </span>
        </h2>
        <div class="qq01" style="background-color: #065a7a; border-left: 1px solid #0b9dbf;
            border-right: 1px solid #0b9dbf">
            <ul>
                <%=contactStr %>
            </ul>
        </div>
        <p id="qq_btn">
            <img src="/Images/qq/pop_img01.png" alt="" /></p>
    </div>
    <p id="qqfr" style="display: none;">
        <img src="/Images/pop_tit02.gif" alt="" /></p>
</div>

<script src="/Js/common.js" type="text/javascript"></script>

