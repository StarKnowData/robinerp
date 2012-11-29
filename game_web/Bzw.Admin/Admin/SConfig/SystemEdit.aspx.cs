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

public partial class Admin_SConfig_SystemEdit : AdminBasePage
{
    string id = "0";

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("03");

        if (Request.QueryString["id"] != null)
        {
            id = Request.QueryString["id"].ToString();
            if (!CommonManager.String.IsInteger(id))
            {
                Alert("警告：\\n\\n请勿非法操作！", null);
				return;
            }
            if (!IsPostBack)
            {
                if (Convert.ToInt32(id) > 0)
                {

                    DataTable dt = new DataTable();
                    string sql = "select * from Web_System Where ID=" + id + "";
					dt = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
                    if (dt.Rows.Count > 0)
                    {
                        txtParaName.Text = dt.Rows[0]["ParaName"].ToString();
                        txtParaValue.Text = dt.Rows[0]["ParaValue"].ToString();
                        txtParaDesc.Text = dt.Rows[0]["Descript"].ToString();
                    }
                    dt.Clear();
                }
            }
        }
    }

    protected void On_btnSubmit(object sender, EventArgs e)
    {
        string paraName = txtParaName.Text.Trim();
		string paraValue = txtParaValue.Text.Trim();
		string paraDesc = txtParaDesc.Text.Trim();

		string sql = "";
        if (Convert.ToInt32(id) > 0)
        {
			sql = @"update Web_System set ParaName=@ParaName,ParaValue=@ParaValue,Descript=@Descript where ID=@ID";

            HttpContext.Current.Application["sc_" + paraName.ToLower()] = paraValue;
        }
        else
        {
			sql = @"insert Web_System (ParaName,ParaValue,Descript) values (@ParaName,@ParaValue,@Descript)";
        }

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@ParaName", DbType.String, paraName )
			.AddInputParameter( "@ParaValue", DbType.String, paraValue )
			.AddInputParameter( "@Descript", DbType.String, paraDesc )
			.AddInputParameter( "@ID", DbType.String, id )
			.Execute();
        
        Response.Redirect("systems.aspx");
        /*
        if (SqlState > 0)
            Limit.outMsgBox("温馨提示：\\n\\n网站参数" + msg + "成功！", "systems.aspx", true);
        else
            Limit.outMsgBox("温馨提示：\\n\\n网站参数" + msg + "失败！", true);*/
    }
}
