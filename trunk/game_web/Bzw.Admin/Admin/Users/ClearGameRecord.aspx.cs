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

public partial class Admin_Users_ClearGameRecord : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

	protected void btnSubmit_Click( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;
		if( !IsValid )
			return;

		if( string.IsNullOrEmpty( txtBeginTime.Text.Trim() ) && string.IsNullOrEmpty( txtEndTime.Text.Trim() ) )
		{
			Alert("请选择起止时间段。",null);
			return;
		}

		string sql = "";
		if( !string.IsNullOrEmpty( txtBeginTime.Text.Trim() ) && CommonManager.String.IsDateTime( txtBeginTime.Text.Trim() ) && ( string.IsNullOrEmpty( txtEndTime.Text.Trim() ) || !CommonManager.String.IsDateTime( txtEndTime.Text.Trim() ) ) )
		{
			//按起始时间删除
			sql = "delete TChangeRecord where EndTime >= '" + txtBeginTime.Text.Trim() + " 00:00:00' ";
		}
		else if( ( string.IsNullOrEmpty( txtBeginTime.Text.Trim() ) || !CommonManager.String.IsDateTime( txtBeginTime.Text.Trim() ) ) && !string.IsNullOrEmpty( txtEndTime.Text.Trim() ) && CommonManager.String.IsDateTime( txtEndTime.Text.Trim() ) )
		{
			//按结束时间删除
			sql = "delete TChangeRecord where EndTime <= '" + txtEndTime.Text.Trim() + " 23:59:59'";
		}
		else if( !string.IsNullOrEmpty( txtBeginTime.Text.Trim() ) && CommonManager.String.IsDateTime( txtBeginTime.Text.Trim() ) && !string.IsNullOrEmpty( txtEndTime.Text.Trim() ) && CommonManager.String.IsDateTime( txtEndTime.Text.Trim() ) )
		{
			//按时间段删除
			sql = "delete TChangeRecord where EndTime between '" + txtBeginTime.Text.Trim() + " 00:00:00' and '" + txtEndTime.Text.Trim() + " 23:59:59'";
		}
    
        if (!string.IsNullOrEmpty(sql))
        {
            DbSession.Default.FromSql(sql).Execute();
            DbSession.Default.FromSql("delete TChangeRecordUser where RecordIndex not in (select id from TchangeRecord )").Execute();
        }
		Alert( "操作成功！", Request.Url.AbsoluteUri );
	}
}
