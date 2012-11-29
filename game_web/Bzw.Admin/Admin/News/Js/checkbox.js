var checkFlag = true;
　　　　function chkall()
　　　　{
 　　　　　　if( checkFlag ) // 全选　
　　　　　　{
  　　　　　　　　var inputs = document.all.tags("input");
  　　　　　　　　for (var i=0; i < inputs.length; i++) // 遍历页面上所有的 input 
  　　　　　　　　{
  　　　　　　　　　　if (inputs[i].type == "checkbox" && inputs[i].id != "CheckAll" )
   　　　　　　　　　　{
    　　　　　　　　　　　　inputs[i].checked = true;
   　　　　　　　　　　}     
  　　　　　　　　}
  　　　　　　　　checkFlag = false;
 　　　　　　}
 　　　　　　else  // 取消全选
 　　　　　　{
  　　　　　　　　var inputs = document.all.tags("INPUT");
  　　　　　　　　for (var i=0; i < inputs.length; i++) // 遍历页面上所有的 input 
  　　　　　　　　{
   　　　　　　　　　　if (inputs[i].type == "checkbox" && inputs[i].id != "CheckAll" )
   　　　　　　　　　　{
    　　　　　　　　　　　　inputs[i].checked = false;
   　　　　　　　　　　}     
  　　　　　　　　}
  　　　　　　　　checkFlag = true;
 　　　　　　}
　　　　}

  　　　　　
			function chkReverse()
			{
				var inputs = document.all.tags("INPUT");
				for (i=0; i < inputs.length;i++)
				{
				　if (inputs[i].type == "checkbox" && inputs[i].id != "CheckAll")
   　　　　　　　　{
						inputs[i].checked = !inputs[i].checked;	
				   }
				}
			}
			
			function allplay()
			{				
				var url = "musiclist.aspx?QueryPls=";
				var inputs = document.all.tags("INPUT");
				for (i=0; i < inputs.length;i++)
				{
				　if (inputs[i].type == "checkbox" && inputs[i].id != "CheckAll")
   　　　　　　　　{
						if(inputs[i].checked)
						{
							url+=","+inputs[i].value;
						}	
				   }
				}
				window.open(url, 'newwindow2', 'height=335, width=515, top=100, left=100,toolbar=no, menubar=no, scrollbars=no, resizable=no, location=no, status=no');
			}
