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
using System.Text;
using Bzw.Data;
using BCST.Common;
using Utility;

public partial class Admin_Pay_FreeCardCount : AdminBasePage
{
    public string FCardCount = string.Empty;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "05" );

		if( !IsPostBack )
		{
			DataTable sd = new DataTable();
			string sql = "select top 1 * from Web_Config";
			sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader( sql );
			if( sd.Rows.Count > 0 )
			{
				txt1Yuan.Value = sd.Rows[0]["FreeCardCount"].ToString();
                FCardCount = sd.Rows[0]["FreeCardCount"].ToString();	
			}
			sd.Clear();
		}
	}

	protected void EditFilt( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;

		if( !IsValid )
			return;
        string sql = @"update Web_Config set FreeCardCount=@FreeCardCount";
		DbSession.Default.FromSql( sql )
            .AddInputParameter("@FreeCardCount", DbType.Int32, (string.IsNullOrEmpty(txt1Yuan.Value.Trim()) || !CommonManager.String.IsInteger(txt1Yuan.Value.Trim())) ? 0 : int.Parse(txt1Yuan.Value.Trim()))			
			.Execute();
		string adminName = AdminInfo["UserName"].ToString();
        string descript = "修改免费卡数量成功，数量由" + FCardCount + "修改为：" + txt1Yuan.Value.Trim();
        string system = Common.GetOS;
        new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);
		CommonManager.Web.RegJs( this, "alert('设置成功！');LocationToMe();", false );
	}
}
