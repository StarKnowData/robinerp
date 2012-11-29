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

public partial class Admin_SConfig_PFPricesE : AdminBasePage
{
	string PropID;
	public string PropName, Price, VipPrice, Descript;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "15" );

		PropID = CommonManager.Web.Request( "id", "" );
		if( !CommonManager.String.IsInteger( PropID ) )
			CommonManager.Web.RegJs( this, "alert('温馨提示：\\n\\n请勿非法操作！');history.back();", false );

		DataTable sd = DbSession.Default.FromSql( "select *  from Web_ClearFasciPropDefine where ID=@ID" )
			.AddInputParameter( "@ID", DbType.Int32, PropID )
			.ToDataTable();

		if( sd.Rows.Count > 0 )
		{
			PropName = sd.Rows[0]["Title"].ToString();
			Price = sd.Rows[0]["Price"].ToString();
			VipPrice = sd.Rows[0]["DecFasci"].ToString();
			Descript = sd.Rows[0]["Description"].ToString();
		}
		sd.Clear();
	}

	protected void EditJpPro( object sender, EventArgs e )
	{
		string sqlPropName, sqlPrice, sqlVipPrice, sqlDescript;
		 
		sqlPropName = CommonManager.Web.RequestForm( "PropName", "" );
		sqlPrice = CommonManager.Web.RequestForm( "Price", "" );
		sqlVipPrice = CommonManager.Web.RequestForm( "VipPrice", "" );
		sqlDescript = CommonManager.Web.RequestForm( "Descript", "" );


		if( sqlDescript.Trim().Length > 25 )
		{
			CommonManager.Web.RegJs( this, "alert('温馨提示：\\n\\n道具说明的字符个数不能超过25！');location.href=location.href;", false );
			return;
		}
		DbSession.Default.FromSql( "update Web_ClearFasciPropDefine set Title=@PropName,Price=@Price,DecFasci=@ClearFasci,Description=@Descript where ID=@ID  " )
			.AddInputParameter( "@PropName", DbType.String, sqlPropName )
			.AddInputParameter( "@Price", DbType.String, sqlPrice )
			.AddInputParameter( "@ClearFasci", DbType.String, sqlVipPrice )
			.AddInputParameter( "@Descript", DbType.String, sqlDescript )
			.AddInputParameter( "@ID", DbType.String, PropID )
			.Execute();
		CommonManager.Web.RegJs( this, "alert('温馨提示：\\n\\n修改道具成功！');location.href=location.href;", false );
	}
}
