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
using BCST.Common;
using Bzw.Data;

public partial class Admin_SConfig_MoneyRankingViewSet : AdminBasePage
{

    protected bool IsOnlyMoney {
        get { 
         string cmdText = "select top 1 MRView from web_config";
         return DbSession.Default.FromSql(cmdText).ToScalar<bool>();
        }
    
    
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("12");


        if (!IsPostBack)
        {
            if (IsOnlyMoney == false)
            {
                this.radio1.Attributes.Add("Checked", "Checked");
                this.radio2.Attributes.Add("Checked", "");
            }
            else
            {

                this.radio1.Attributes.Add("Checked", "");
                this.radio2.Attributes.Add("Checked", "Checked");
            
            }
        
        }


    }


    protected void EditPric(object sender, EventArgs e)
    {
        string value = CommonManager.Web.RequestForm("yes", "");

        string cmdText="update web_config set MRView=@MRView";

        int cmdResult= DbSession.Default.FromSql(cmdText)
        .AddInputParameter("@MRView", DbType.Boolean, value)
        .Execute();

        if (cmdResult > 0)
        {
            msg.Text = "修改成功！" + DateTime.Now;

        }
        else
        {

            msg.Text = "修改失败";
        }
       



    }
}
