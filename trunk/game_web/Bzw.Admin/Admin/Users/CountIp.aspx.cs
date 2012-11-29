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
using Bzw.Data;
using BCST.Common;

public partial class Admin_Users_CountIp : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");

        string beginTime, EndTime, IPS, DayCount,Mac;
		beginTime = CommonManager.Web.Request("tt",""); //Limit.editCharacter(Limit.getFormValue("tt"));
		EndTime = CommonManager.Web.Request( "nn", "" ); //Limit.editCharacter(Limit.getFormValue("nn"));
		IPS = CommonManager.Web.Request( "ip", "" ); //Limit.editCharacter(Limit.getFormValue("ip"));
		DayCount = CommonManager.Web.Request( "dd", "" ); //Limit.editCharacter(Limit.getFormValue("dd"));
        Mac = CommonManager.Web.Request("mac", "");
        DataTable sd = new DataTable();
        string sql = "select count(*) as bbr,CONVERT(varchar(12),CONVERT(datetime,RegisterTM),110)as ddr from Web_Users where CONVERT(datetime,RegisterTM)>='" + beginTime + "' and CONVERT(datetime,RegisterTM)<='" + EndTime + "' and RegisterIP='" + IPS + "' group by CONVERT(varchar(12),CONVERT(datetime,RegisterTM),110) order by CONVERT(varchar(12),CONVERT(datetime,RegisterTM),110) asc";
        
        //Response.Write(sql);
        //Response.End();
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if(sd.Rows.Count>0)
        {
			IpCount.DataSource = sd;
			IpCount.DataBind();
        }
        else
        {
            this.NoIpCount.Visible = true;
        }
        sd.Clear();
    }
}
