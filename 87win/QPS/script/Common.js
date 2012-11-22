//Deleting values of all Text type,Checkbox type and Textarea type.
function ClearAllTextValue()
{
    var elements = document.all.tags("input");
    
    for ( var i=0; i<elements.length; i++)
    {
        if (elements[i].type == "text")
        {
            elements[i].value = "";
        }
        else if (elements[i].type == "checkbox")
        {
            elements[i].checked = false;
        }
    }

    var txtAreas = document.all.tags("textarea");
    
    for ( var i=0; i<txtAreas.length; i++ )
    {
        txtAreas[i].value = "";
    }
}

function openURL(URL)
{
    parent.mainFrame.location=URL;
}

//Go to new URL included parameter uid.
function openURLByUId(URL,ctrlId)
{
    URL += "?uid=";
    URL += document.getElementById(ctrlId).value;
    parent.mainFrame.location = URL;
}

//Check all checkboxes in the page.
function ChooseAllCheckbox(obj)
{
    var elements = document.all.tags("input");
    for (var i=0;i<elements.length;i++)
    {
        if (elements[i].type == "checkbox" && !(elements[i].disabled) )
        {
            if ( obj.checked )
            {
                elements[i].checked = true;
            }
            else
            {
                elements[i].checked = false;
            }
        }
    }
}

//whether exist some checked checkbox
//objId is the id of the checkbox of choosing all ones
function IsChooseSome(obj,ckbId)
{
    var elements = document.all.tags("input");
    var i = 0;
    for (i = 0;i < elements.length;i++)
    {
        if ( elements[i].type == "checkbox" && elements[i].checked && elements[i].id != ckbId)
        {
            if (obj.id == "btnDel")
            {
                return confirm("确定要删除吗?");
            }
            return true;
        }
    }
    if ( i == elements.length )
    {
        alert('请选择要操作的数据!');
        return false;
    }
}

//Display current date in control 'objId'.
function GetCurrDate(objId)
{
    var today = new Date().getFullYear() + "-";
    if ( new Date().getMonth() < 9 )
    {
        today += "0" + ( new Date().getMonth() + 1 );
    }
    else
    {
        today += new Date().getMonth() + 1;
    }
    today += "-";
    if ( new Date().getDate() < 10 )
    {
        today += "0" + new Date().getDate();
    }
    else
    {
        today += new Date().getDate();
    }
    document.getElementById(objId).value = today;
}

function CheckEmpty(objId)
{
    if (document.getElementById(objId).value == "")
    {
        alert("");
        document.getElementById(objId).focus();
        return false;
    }
    return true;
}

//Limit values' length
function limitTxtLength(objid)
{
    var v = document.getElementById(objid).value;
    if (v.length > 150)
    {
        alert("手术史太长,请重新填写!");
        document.getElementById(objid).focus();
    }
}