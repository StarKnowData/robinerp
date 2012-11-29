using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

public partial class Admin_Games_RoomRuleSet : AdminBasePage
{
    public string RoomRule;
    
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

        if (Request["RoomRule"] != "")
        {
            RoomRule = Request["RoomRule"].ToString();
        }
    }
    public string getRoomRule(int rulevalue)
    {
        int temp;
        temp = Convert.ToInt32(RoomRule) & rulevalue;
        if (temp == rulevalue)
        {
            return "checked";
        }
        else
        {
            return "";
        }

    }
    
}
