/*==================================/
*
*功能：
* 实现从客户端在DataGrid中
* 选择一行或多行的效果 
*
===================================*/

//在客户端选择dataGrid中的一行，并将行号记录在txtSelectIndex域中
function getDgdSelectIndex(txtSelectIndex)
{
	var dgdTable = event.srcElement;
	if (dgdTable == null) return;

	//回溯，获取DataGrid在客户端的Table
	while (dgdTable.tagName != 'TABLE')
	{
		dgdTable = dgdTable.parentElement;
	}

	var curRow = event.srcElement;
	if  (curRow == null) return;
	
	//回溯，获取客户端选择行
	while (curRow.tagName != 'TR')
	{
		curRow = curRow.parentElement;
	}
	
	//记录行号
	var oSelectIndex = document.getElementById(txtSelectIndex);

	for (i = 1; i < dgdTable.rows.length; i++)
	{
		if  (curRow == dgdTable.rows[i])
		{
			if (oSelectIndex != null)
				oSelectIndex.value = i - 1;
			dgdTable.rows[i].className = 'dgdSelectedItem';
		}
		else
		{
			dgdTable.rows[i].className = 'dgdItem';
		}
	}
}

//选定DataGrid的行，并将该行的CheckBox置为选择状态（或取消该行的选择状态）
//lastSelectedRowIndex: 最后选定行在当前页的索引
function checkDgdRow(lastSelectedRowIndex)
{
	var dgdTable = event.srcElement;
	if (dgdTable == null) return;

	//回溯，获取DataGrid在客户端的Table
	while (dgdTable.tagName != 'TABLE')
	{
		dgdTable = dgdTable.parentElement;
	}

	var oCurRow = event.srcElement;
	if  (oCurRow == null) return;
			
	if (event.srcElement.tagName == 'INPUT')
		if (event.srcElement.type == 'checkbox')
			var srcElementIsCheckBox = true; //事件源为CheckBox
			
	//回溯，获取客户端选择行
	while (oCurRow.tagName != 'TR')
	{
		oCurRow = oCurRow.parentElement;
	}
			
	for (i = 1; i < dgdTable.rows.length; i++)
	{
		if  (oCurRow == dgdTable.rows[i])
		{
			//设置选择行
			for (var j=0; j < oCurRow.all.length; j++)
			{
				//获取选择行的CheckBox
				if (oCurRow.all[j].tagName == 'INPUT')
					if (oCurRow.all[j].type == 'checkbox' && !oCurRow.all[j].disabled)
					{
						var oSelectedRowCbx = oCurRow.all[j];
							
						if (oSelectedRowCbx.checked)
						{
							if (!srcElementIsCheckBox)
							{
								oSelectedRowCbx.checked = false;
								dgdTable.rows[i].className = 'dgdItem';
							}
							else
								dgdTable.rows[i].className = 'dgdSelectedItem';
						}
						else 
						{
							if (!srcElementIsCheckBox)
							{
								oSelectedRowCbx.checked = true;
								dgdTable.rows[i].className = 'dgdSelectedItem';
							}
							else
								dgdTable.rows[i].className = 'dgdItem';
							
							//记录最后选定行在当前页的索引
							if (document.all[lastSelectedRowIndex] != null)
								document.all[lastSelectedRowIndex].value = i - 1;
						}
						break;
					}
			}
		}
	}
}