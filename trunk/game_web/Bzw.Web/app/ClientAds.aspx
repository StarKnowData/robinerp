<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.ClientAds"%>
  <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html xmlns="http://www.w3.org/1999/xhtml" >

<style type="text/css">
 
body {
	margin: 0px;
	padding: 0px;
	border:0px;
}
 
 
</style>
<head runat="server">
    <title>Œﬁ±ÍÃ‚“≥</title>
    <script type="text/javascript" src="/public/js/jquery.js"></script>
    <script type="text/javascript" src="/public/js/public.js"></script>
    
    <script type="text/javascript">
        var AdTypeId = GetRequest("id", "");
        $(document).ready(function() {
            $.get('/upload/xml/GameAd.xml', function(d) {
                $(d).find('item').each(function() {
                    var $item = $(this);
                    var id = $item.attr("id");
                    var content = $item.find("Content").text();
                    if (id == AdTypeId)
                        displayHtml(content);
                //    MM_preloadImages();
                });
            });
        });



        function displayHtml(_content) { 
       $("#AdContent").html(_content);
   }
   

    
    
    
    </script>
    
    
</head>
<body scroll="no" >
    
    <div id="AdContent" align="center" style="padding:0 auto; margin:0 auto;   " >
    
    </div>
 
</body>
</html>
