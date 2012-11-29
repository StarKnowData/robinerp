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

public partial class Admin_Pay_Rate : AdminBasePage
{
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
				txt1Yuan.Value = sd.Rows[0]["Con_MoneyChangeRate"].ToString();
                txtUserMaxPayMoney.Text = sd.Rows[0]["UserMaxPayMoney"].ToString();
                txtPointChangeRate.Text = sd.Rows[0]["Con_PointChangeRate"].ToString();
				/*txtJunnet.Value = sd.Rows[0]["Yeepay_Rate_Junnet"].ToString();
				txtNetBank.Value = sd.Rows[0]["Yeepay_Rate_NetBank"].ToString();
				txtSzx.Value = sd.Rows[0]["Yeepay_Rate_Szx"].ToString();
				txtUnicom.Value = sd.Rows[0]["Yeepay_Rate_Unicom"].ToString();
				txtYPCard.Value = sd.Rows[0]["Yeepay_Rate_YPCard"].ToString();*/
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
		string sql = @"update Web_Config set Con_MoneyChangeRate=@Con_MoneyChangeRate,
					Yeepay_Rate_Junnet=@Yeepay_Rate_Junnet,
					Yeepay_Rate_NetBank=@Yeepay_Rate_NetBank,
					Yeepay_Rate_Szx=@Yeepay_Rate_Szx,
					Yeepay_Rate_Unicom=@Yeepay_Rate_Unicom,
					Yeepay_Rate_YPCard=@Yeepay_Rate_YPCard,
                    UserMaxPayMoney=@UserMaxPayMoney,
                    Con_PointChangeRate=@Con_PointChangeRate
                    ";

		/*DbSession.Default.FromSql( sql )
			.AddInputParameter( "@Con_MoneyChangeRate", DbType.Int32, ( string.IsNullOrEmpty( txt1Yuan.Value.Trim() ) || !CommonManager.String.IsInteger( txt1Yuan.Value.Trim() ) ) ? 0 : int.Parse( txt1Yuan.Value.Trim() ) )
			.AddInputParameter( "@Yeepay_Rate_Junnet", DbType.Int32, ( string.IsNullOrEmpty( txtJunnet.Value.Trim() ) || !CommonManager.String.IsInteger( txtJunnet.Value.Trim() ) ) ? 0 : int.Parse( txtJunnet.Value.Trim() ) )
			.AddInputParameter( "@Yeepay_Rate_NetBank", DbType.Int32, ( string.IsNullOrEmpty( txtNetBank.Value.Trim() ) || !CommonManager.String.IsInteger( txtNetBank.Value.Trim() ) ) ? 0 : int.Parse( txtNetBank.Value.Trim() ) )
			.AddInputParameter( "@Yeepay_Rate_Szx", DbType.Int32, ( string.IsNullOrEmpty( txtSzx.Value.Trim() ) || !CommonManager.String.IsInteger( txtSzx.Value.Trim() ) ) ? 0 : int.Parse( txtSzx.Value.Trim() ) )
			.AddInputParameter( "@Yeepay_Rate_Unicom", DbType.Int32, ( string.IsNullOrEmpty( txtUnicom.Value.Trim() ) || !CommonManager.String.IsInteger( txtUnicom.Value.Trim() ) ) ? 0 : int.Parse( txtUnicom.Value.Trim() ) )
			.AddInputParameter( "@Yeepay_Rate_YPCard", DbType.Int32, ( string.IsNullOrEmpty( txtYPCard.Value.Trim() ) || !CommonManager.String.IsInteger( txtYPCard.Value.Trim() ) ) ? 0 : int.Parse( txtYPCard.Value.Trim() ) )
			.Execute();*/
		DbSession.Default.FromSql(sql)
			.AddInputParameter("@Con_MoneyChangeRate", DbType.Int32, (string.IsNullOrEmpty(txt1Yuan.Value.Trim()) || !CommonManager.String.IsInteger(txt1Yuan.Value.Trim())) ? 0 : int.Parse(txt1Yuan.Value.Trim()))
			.AddInputParameter("@Yeepay_Rate_Junnet", DbType.Int32, 0)
			.AddInputParameter("@Yeepay_Rate_NetBank", DbType.Int32, 0)
			.AddInputParameter("@Yeepay_Rate_Szx", DbType.Int32, 0)
			.AddInputParameter("@Yeepay_Rate_Unicom", DbType.Int32, 0)
			.AddInputParameter("@Yeepay_Rate_YPCard", DbType.Int32, 0)
            .AddInputParameter("@UserMaxPayMoney",DbType.Int32,Convert.ToInt32(txtUserMaxPayMoney.Text.Trim()))
            .AddInputParameter("@Con_PointChangeRate",DbType.Int64,Convert.ToInt64(txtPointChangeRate.Text.Trim()))
			.Execute();

		string adminName = AdminInfo["UserName"].ToString();
		string descript = "修改兑换比例,充值限制成功";
		string system = Common.GetOS;
		new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
		CommonManager.Web.RegJs( this, "alert('设置成功！');LocationToMe();", false );
	}
}
