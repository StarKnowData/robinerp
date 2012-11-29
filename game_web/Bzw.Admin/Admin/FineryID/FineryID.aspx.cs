using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Bzw.Data;
using System.Data;
using BCST.Common;

namespace Bzw.Web.Admin.FineryID
{
	public partial class FineryID1 : AdminBasePage
	{
		protected void Page_Load( object sender, EventArgs e )
		{
			AdminPopedom.IsHoldModel( "14" );
			this.msg.Text = "";
			this.msgup.Text = "";
			if( !IsPostBack )
			{
				BindData();
			}
		}

		//添加靓号
		protected void Button1_Click( object sender, EventArgs e )
		{
			this.msg.Text = "";
			string fineryid = this.FineryID.Text.ToString().Trim();
			string price = this.pr.Text.ToString().Trim();
			string bewrite = Utility.Common.CutStringUnicode(this.bewriteTB.Text.ToString(),20,"");
			if( !Utility.Common.IsNumber( fineryid )|| fineryid.Length<3||fineryid.Length>9)
			{
				this.msg.Text = "很抱歉，靓号需为数字且长度为3-9位";
				return;
			}
			if( !Utility.Common.IsIntegrity( price ) )
			{
				this.msg.Text = "很抱歉，价格需为数字";
				return;
			}
			//判断TUser或Web_FineryID表是否存在添加的靓号ID
			string sql = @"select * from Web_FineryID where FineryID=@FineryID";
			object obj = DbSession.Default.FromSql( sql )
					.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
					.ToScalar();
			int cout = Convert.ToInt32( obj );
			if( cout > 0 )
			{
				this.msg.Text = "很抱歉，靓号已存在或已被用户注册";
				return;
			}
			else
			{
				cout = 0;
				sql = @"insert into Web_FineryID(FineryID, Price, IsBuy, IsUse,IsSale,IsTop,Explain) values(@FineryID,@Price,0,0,@IsSale,@IsTop,@Explain)";
				cout = DbSession.Default.FromSql( sql )
					.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
					.AddInputParameter( "@Price", DbType.Int32, price )
					.AddInputParameter( "@IsSale", DbType.Int32, sjRDO.SelectedItem.Value )
					.AddInputParameter( "@IsTop", DbType.Int32, tjRDO.SelectedItem.Value )
					.AddInputParameter("@Explain",DbType.String,bewrite)
					.Execute();
				if( cout > 0 )
				{
					CommonManager.Web.RegJs( this, "alert('恭喜您！添加成功')", false );
				}
				else
				{
					CommonManager.Web.RegJs( this, "alert('抱歉！添加失败')", false );
				}

			}
		}

		//修改靓号默认价格
		protected void Button2_Click( object sender, EventArgs e )
		{
			
			this.msgup.Text = "";
			string price=this.PriceTX.Text.ToString();
			string reg = this.rulesTX.Text.ToString();
			if( !Utility.Common.IsIntegrity( price ) )
			{
				this.msgup.Text = "很抱歉，价格只能为正整数";
				return;
			}
			string sql = "update Web_Config set FineryIDDefaultPrice=@Price,FineryIDRegex=@Reg";
			int cout = DbSession.Default.FromSql( sql )
			.AddInputParameter( "@Price", DbType.Int32, price )
			.AddInputParameter("@Reg",DbType.String,reg)
			.Execute();
			if( cout > 0 )
			{
				CommonManager.Web.RegJs(this,"alert('恭喜您！修改成功')",false);
				BindData();
			}
			else
			{
				CommonManager.Web.RegJs( this, "alert('抱歉！修改失败')", false );
			}
		}

		public void BindData()
		{
			string sql = "select FineryIDDefaultPrice,FineryIDRegex from Web_Config";
			DataTable tb = DbSession.Default.FromSql( sql ).ToDataTable();
			if( tb.Rows.Count <= 0 )
			{
				CommonManager.Web.RegJs( this, "alert('未知错误!');", false );
				return;
			}
			DataRow row = tb.Rows[0];
			PriceTX.Text = row["FineryIDDefaultPrice"].ToString();
			rulesTX.Text = row["FineryIDRegex"].ToString();
		}
	}
}
