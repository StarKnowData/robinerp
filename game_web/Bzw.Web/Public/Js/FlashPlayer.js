function flashPlayer(width, height, bottom){
    this.width = width;
    this.height = height;
    this.bottom = bottom;
    
    //:<<<<=高度注意=>>>>:
    //只支持JPG格式的图片，如果把GIF或其他格式的图片文件的扩展名直接改成JPG也不行
    //如果网站设置的端口有冲突的时，该FLASH不能正常显示，只有灰屏
    //http://myjs.chinaz.com/ http://myjs.chinaz.com/jsfile/content1.asp?class=38&cid=1275
    //http://www.webjx.com/htmldata/2005-12-10/1134212650.html
    this.pics = new Array();
    this.links = new Array();
    this.texts = new Array();
    
    this.add = Add;
    this.play = Play;
    
    function Add(pic, link, text){
        var index = this.pics.length;
        this.pics[index] = pic;
        this.links[index] = link;
        this.texts[index] = text;
        //alert(pic+text+link);
    }
    
    function Play(){
        var fsh_width = this.width;
        var fsh_height = this.height;
        var text_height = this.bottom;
		var swf_height = this.height + this.bottom;
		var fsh_pics = '';
		var fsh_links = '';
		var fsh_texts = '';
		
		var length = this.pics.length;
		for(i=0; i<length; i++){
		    fsh_pics += '|'+ this.pics[i]; 
		    fsh_links += '|'+ this.links[i];
		    fsh_texts += '|'+ this.texts[i];
		}
		if(fsh_pics.length > 0){
		    fsh_pics = fsh_pics.substring(1);
		    fsh_links = fsh_links.substring(1);
		    fsh_texts = fsh_texts.substring(1);
		}

	    document.write('<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="'+ fsh_width +'" height="'+ swf_height +'">');
	    document.write('<param name="allowScriptAccess" value="sameDomain"><param name="movie" value="/Images/Flash/FlashPlayer.swf"><param name="quality" value="high"><param name="bgcolor" value="white">');
	    document.write('<param name="menu" value="false"><param name=wmode value="opaque">');
	    document.write('<param name="FlashVars" value="pics='+ fsh_pics +'&links='+ fsh_links +'&texts='+ fsh_texts +'&borderwidth='+ fsh_width +'&borderheight='+ fsh_height +'&textheight='+ text_height +'">');
	    document.write('<embed src="/Images/Flash/FlashPlayer.swf" wmode="opaque" FlashVars="pics='+ fsh_pics +'&links='+ fsh_links +'&texts='+ fsh_texts +'&borderwidth='+ fsh_width +'&borderheight='+ fsh_height +'&textheight='+ text_height +'" menu="false" bgcolor="white" quality="high" width="'+ fsh_width +'" height="'+ swf_height +'" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />');
	    document.write('</object>');
    }
}