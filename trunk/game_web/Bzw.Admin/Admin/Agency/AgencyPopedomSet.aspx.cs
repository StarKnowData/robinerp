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
using UiCommon;

public partial class Admin_Agency_AgencyPopedomSet : AdminBasePage
{
	protected string AgencyUserName = "";
	protected string AgencyTrueName = "";

	protected void Page_Load( object sender, EventArgs e )
	{
        AdminPopedom.IsHoldModel("17");
		cbxIsPickUpCashToAgency.Text = "允许提取直属代理的金币" ;
		cbxIsGiveToAgency.Text = "允许对直属代理充金币" ;
		cbxIsPickUpCashToPlayer.Text = "允许提取直属玩家的金币" ;
		cbxIsGiveToPlayer.Text = "允许对直属玩家充金币";

		if( IsPostBack )
			return;

		dataBind();
	}
	public void dataBind()
	{
		string agencyname = CommonManager.Web.RequestUrlDecode( "agencyName", "" );

		if( string.IsNullOrEmpty( agencyname ) )
			return;

		string sql = "Select a.*,b.TrueName from Web_AgencyPopeSet a inner join Web_Agency b ON a.AgencyName= b.AgencyName Where a.AgencyName = @AgencyName";

		DataTable dt = DbSession.Default.FromSql( sql )
			.AddInputParameter( "@AgencyName", DbType.String, agencyname )
			.ToDataTable();

		if( dt.Rows.Count > 0 )
		{
			DataRow dr = dt.Rows[0];

			AgencyUserName = agencyname;
			AgencyTrueName = dr["TrueName"].ToString();

			cbxIsAddAgency.Checked = ( dr["IsAddAgency"].ToString() == "1" );
			cbxIsGiveToAgency.Checked = ( dr["IsGiveToAgency"].ToString() == "1" );
			cbxIsGiveToPlayer.Checked = ( dr["IsGiveToPlayer"].ToString() == "1" );
			cbxIsPickUpCashToAgency.Checked = ( dr["IsPickUpCashToAgency"].ToString() == "1" );
			cbxIsPickUpCashToPlayer.Checked = ( dr["IsPickUpCashToPlayer"].ToString() == "1" );
		}
		else
		{
			//如果不存在记录，则增加一条
			DbSession.Default.FromSql( "insert Web_AgencyPopeSet (AgencyName,IsAddAgency,IsPickUpCashToAgency,IsPickUpCashToPlayer,IsGiveToAgency,IsGiveToPlayer) values (@AgencyName,0,0,0,0,0)" ).AddInputParameter( "@AgencyName", DbType.String, agencyname ).Execute();
		}

	}
	protected void btnMondify_Click( object sender, EventArgs e )
	{
		string agencyname = CommonManager.Web.RequestUrlDecode( "agencyName", "" );

		if( string.IsNullOrEmpty( agencyname ) )
			return;

		string sql = @"Update Web_AgencyPopeSet set IsAddAgency=@IsAddAgency,
					IsPickUpCashToAgency=@IsPickUpCashToAgency,
					IsPickUpCashToPlayer=@IsPickUpCashToPlayer,
					IsGiveToAgency=@IsGiveToAgency,
					IsGiveToPlayer=@IsGiveToPlayer 
					where AgencyName=@AgencyName";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@IsAddAgency", DbType.Int32, cbxIsAddAgency.Checked ? 1 : 0 )
			.AddInputParameter( "@IsPickUpCashToAgency", DbType.Int32, cbxIsPickUpCashToAgency.Checked ? 1 : 0 )
			.AddInputParameter( "@IsPickUpCashToPlayer", DbType.Int32, cbxIsPickUpCashToPlayer.Checked ? 1 : 0 )
			.AddInputParameter( "@IsGiveToAgency", DbType.Int32, cbxIsGiveToAgency.Checked ? 1 : 0 )
			.AddInputParameter( "@IsGiveToPlayer", DbType.Int32, cbxIsGiveToPlayer.Checked ? 1 : 0 )
			.AddInputParameter( "@AgencyName", DbType.String, agencyname )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('权限设置成功！');location.href='" + Utility.Common.UrlValue + "';", false );
	}
}
