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
using Utility;
using BCST.Common;
using Bzw.Data;

public partial class Admin_Prizes_PrizesHEdit : AdminBasePage
{
    string Logid;
    public string PName, PUser, Ptime, PNameUser, Ptel, Paddress, PIsCash, PUserRemark;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("11");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			Logid = tmp; //Limit.editCharacter(Limit.getFormValue("id"));

        DataTable sd = new DataTable();
        string sql = "select *,b.Award_Name,c.UserName from Web_AwardLog a,Web_Award b,TUsers c "
                        +"where a.Award_ID=b.Award_ID and a.UserID=c.UserID and log_id=" + Logid + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
            PName = sd.Rows[0]["Award_Name"].ToString();
            PUser = sd.Rows[0]["UserName"].ToString();
            Ptime = sd.Rows[0]["AwardTime"].ToString();
            PNameUser = sd.Rows[0]["TrueName"].ToString();
            Ptel = sd.Rows[0]["Phone"].ToString();
            Paddress = sd.Rows[0]["Address"].ToString();
            PIsCash = sd.Rows[0]["IsCash"].ToString();
			PUserRemark = sd.Rows[0]["UserRemark"].ToString();
        }
        sd.Clear();
    }

    protected void Prizes_Edit(object sender, EventArgs e)
    {
        string sqlIsCash;
		sqlIsCash = CommonManager.Web.RequestForm( "IsCash", "0" ); //Limit.editCharacter(Limit.getFormValue("IsCash"));

		string sql = "update Web_AwardLog set IsCash=@IsCash where Log_id=@LogID";

		int SqlState = DbSession.Default.FromSql( sql )
			.AddInputParameter( "@IsCash", DbType.String, sqlIsCash )
			.AddInputParameter( "@LogID", DbType.String, Logid )
			.Execute();


        /*Hashtable ind = new Hashtable();
        ind.Add("IsCash", sqlIsCash);
        int SqlState = sqlconn.sqlExecute(ind, "[Web_AwardLog]", "Log_id=" + Logid + "", 2);
        ind.Clear();*/


		string adminName = AdminInfo["UserName"].ToString();
        string descript = "修改兑奖记录！";
        string system = Common.GetOS;

        if (SqlState >= 0)
        {
            new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);
            Alert("温馨提示：\\n\\n兑奖记录修改成功！", "PrizesH.aspx");
        }
        else
        {
            new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 0);
			Alert( "温馨提示：\\n\\n兑奖记录修改失败！", null );
        }
    }
}
