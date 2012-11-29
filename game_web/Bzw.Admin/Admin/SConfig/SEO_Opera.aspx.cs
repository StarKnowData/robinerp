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
using Bzw.WebLibrary;

public partial class Admin_SConfig_SEO_Opera :AdminBasePage
{

	protected void Page_Load( object sender, EventArgs e )
	{

		if( !IsPostBack )
		{
			txtTitle_Default.Text = SeoConfig.Config.DefaultSeo.Title;
			txtKey_Default.Text = SeoConfig.Config.DefaultSeo.Keyword;
			txtDesc_Default.Text = SeoConfig.Config.DefaultSeo.Description;

			txtTitle_Index.Text = SeoConfig.Config.IndexSeo.Title;
			txtKey_index.Text = SeoConfig.Config.IndexSeo.Keyword;
			txtDesc_index.Text = SeoConfig.Config.IndexSeo.Description;

			txtTitle_Reg.Text = SeoConfig.Config.Register.Title;
			txtKey_Reg.Text = SeoConfig.Config.Register.Keyword;
			txtDesc_Reg.Text = SeoConfig.Config.Register.Description;

			txtTitle_Down.Text = SeoConfig.Config.DownPageSeo.Title;
			txtKey_Down.Text = SeoConfig.Config.DownPageSeo.Keyword;
			txtDesc_Down.Text = SeoConfig.Config.DownPageSeo.Description;

			txtTitle_GameInfo.Text = SeoConfig.Config.GameInfoSeo.Title;
			txtKey_GameInfo.Text = SeoConfig.Config.GameInfoSeo.Keyword;
			txtDesc_GameInfo.Text = SeoConfig.Config.GameInfoSeo.Description;

			txtTitle_Pay.Text = SeoConfig.Config.PaySeo.Title;
			txtKey_Pay.Text = SeoConfig.Config.PaySeo.Keyword;
			txtDesc_Pay.Text = SeoConfig.Config.PaySeo.Description;
/*活动页面
			txtTitle_Activity.Text = SeoConfig.Config.ActivitySeo.Title;
			txtKey_Activity.Text = SeoConfig.Config.ActivitySeo.Keyword;
			txtDesc_Activity.Text = SeoConfig.Config.ActivitySeo.Description;

 * */
			txtTitle_NewsList.Text = SeoConfig.Config.NewsListSeo.Title;
			txtKey_NewsList.Text = SeoConfig.Config.NewsListSeo.Keyword;
			txtDesc_NewsList.Text = SeoConfig.Config.NewsListSeo.Description;

			txtTitle_Prize.Text =  SeoConfig.Config.PrizeSeo.Title;
			txtKey_Prize.Text = SeoConfig.Config.PrizeSeo.Keyword;
			txtDesc_Prize.Text = SeoConfig.Config.PrizeSeo.Description;

			txtTitle_FAQ.Text = SeoConfig.Config.FAQSeo.Title;
			txtKey_FAQ.Text = SeoConfig.Config.FAQSeo.Keyword;
			txtDesc_FAQ.Text = SeoConfig.Config.FAQSeo.Description;

			txtTitle_Rank.Text = SeoConfig.Config.RankSeo.Title;
			txtKey_Rank.Text = SeoConfig.Config.RankSeo.Keyword;
			txtDesc_Rank.Text = SeoConfig.Config.RankSeo.Description;

			txtTitle_PrizeRank.Text = SeoConfig.Config.PrizeRank.Title;
			txtKey_PrizeRank.Text = SeoConfig.Config.PrizeRank.Keyword;
			txtDesc_PrizeRank.Text = SeoConfig.Config.PrizeRank.Description;

			//////////
			txtTitle_NetPay.Text = SeoConfig.Config.NetPaySeo.Title;
			txtKey_NetPay.Text = SeoConfig.Config.NetPaySeo.Keyword;
			txtDesc_NetPay.Text = SeoConfig.Config.NetPaySeo.Description;

			txtTitle_AliPay.Text = SeoConfig.Config.AliPaySeo.Title;
			txtKey_AliPay.Text = SeoConfig.Config.AliPaySeo.Keyword;
			txtDesc_AliPay.Text = SeoConfig.Config.AliPaySeo.Description;

			txtTitle_KuaiQian.Text = SeoConfig.Config.KuaiQianSeo.Title;
			txtKey_KuaiQian.Text = SeoConfig.Config.KuaiQianSeo.Keyword;
			txtDesc_KuaiQian.Text = SeoConfig.Config.KuaiQianSeo.Description;

			txtTitle_TotalPrize.Text = SeoConfig.Config.TotalPrizeSeo.Title;
			txtKey_TotalPrize.Text = SeoConfig.Config.TotalPrizeSeo.Keyword;
			txtDesc_TotalPrize.Text = SeoConfig.Config.TotalPrizeSeo.Description;

			txtTitle_DDZRank.Text = SeoConfig.Config.DDZRankSeo.Title;
			txtKey_DDZRank.Text = SeoConfig.Config.DDZRankSeo.Keyword;
			txtDesc_DDZRank.Text = SeoConfig.Config.DDZRankSeo.Description;

			txtTitle_NNTotalRank.Text = SeoConfig.Config.NNTotalRankSeo.Title;
			txtKey_NNTotalRank.Text = SeoConfig.Config.NNTotalRankSeo.Keyword;
			txtDesc_NNTotalRank.Text = SeoConfig.Config.NNTotalRankSeo.Description;

			txtTitle_NNRank.Text = SeoConfig.Config.NNRankSeo.Title;
			txtKey_NNRank.Text = SeoConfig.Config.NNRankSeo.Keyword;
			txtDesc_NNRank.Text = SeoConfig.Config.NNRankSeo.Description;

			txtTitle_WalletRank.Text = SeoConfig.Config.WalletRankSeo.Title;
			txtKey_WalletRank.Text = SeoConfig.Config.WalletRankSeo.Keyword;
			txtDesc_WalletRank.Text = SeoConfig.Config.WalletRankSeo.Description;

			txtTile_Promoter.Text = SeoConfig.Config.PromoterSeo.Title;
			txtKey_Promoter.Text = SeoConfig.Config.PromoterSeo.Keyword;
			txtDesc_Promoter.Text = SeoConfig.Config.PromoterSeo.Description;

			txtTitle_RankDetail.Text = SeoConfig.Config.RankDetail.Title;
			txtKey_RankDetail.Text = SeoConfig.Config.RankDetail.Keyword;
			txtDesc_RankDetail.Text = SeoConfig.Config.RankDetail.Description;

            txtTitle_PropList.Text = SeoConfig.Config.PropBuyListSeo.Title;
            txtKey_PropList.Text = SeoConfig.Config.PropBuyListSeo.Keyword;
            txtDesc_PropList.Text = SeoConfig.Config.PropBuyListSeo.Description;


            txtTitle_UserPicture.Text = SeoConfig.Config.Userpicture.Title;
            txtKey_UserPicture.Text = SeoConfig.Config.Userpicture.Keyword;
            txtDesc_UserPicture.Text = SeoConfig.Config.Userpicture.Description;


		}
	}

	protected void EditFilt( object sender, EventArgs e )
	{
		if( txtTitle_Default.Text.Trim().Length > 500 )
		{
			lblMsg.Text = "保存失败：标题的字符个数不能超过500！";
			return;
		}
		
		if( txtKey_Default.Text.Trim().Length > 500 )
		{
			lblMsg.Text = "保存失败：关键字的字符个数不能超过500！";
			return;
		}

		if( txtDesc_Default.Text.Trim().Length > 500 )
		{
			lblMsg.Text = "保存失败：描述内容的字符个数不能超过500！";
			return;
		}
		SeoConfig model = new SeoConfig();
		model.DefaultSeo = new Seo( txtTitle_Default.Text.Trim(), txtKey_Default.Text.Trim(), txtDesc_Default.Text.Trim() );
		model.IndexSeo = new Seo( txtTitle_Index.Text.Trim(), txtKey_index.Text.Trim(), txtDesc_index.Text.Trim() );
		model.Register = new Seo(txtTitle_Reg.Text.Trim(),txtKey_Reg.Text.Trim(),txtDesc_Reg.Text.Trim());
		model.DownPageSeo = new Seo( txtTitle_Down.Text.Trim(), txtKey_Down.Text.Trim(), txtDesc_Down.Text.Trim() );
		model.GameInfoSeo = new Seo( txtTitle_GameInfo.Text.Trim(), txtKey_GameInfo.Text.Trim(), txtDesc_GameInfo.Text.Trim() );
		model.PaySeo = new Seo( txtTitle_Pay.Text.Trim(), txtKey_Pay.Text.Trim(), txtDesc_Pay.Text.Trim() );
		//model.ActivitySeo = new Seo( txtTitle_Activity.Text.Trim(), txtKey_Activity.Text.Trim(), txtDesc_Activity.Text.Trim() );
		model.NewsListSeo = new Seo( txtTitle_NewsList.Text.Trim(), txtKey_NewsList.Text.Trim(), txtDesc_NewsList.Text.Trim() );
		model.PrizeSeo = new Seo( txtTitle_Prize.Text.Trim(), txtKey_Prize.Text.Trim(), txtDesc_Prize.Text.Trim() );
		model.FAQSeo = new Seo( txtTitle_FAQ.Text.Trim(), txtKey_FAQ.Text.Trim(), txtDesc_FAQ.Text.Trim() );
		model.RankSeo = new Seo( txtTitle_Rank.Text.Trim(), txtKey_Rank.Text.Trim(), txtDesc_Rank.Text.Trim() );
		model.PrizeRank = new Seo(txtTitle_PrizeRank.Text.Trim(),txtKey_PrizeRank.Text.Trim(),txtDesc_PrizeRank.Text.Trim());
		model.NetPaySeo = new Seo( txtTitle_NetPay.Text.Trim(), txtKey_NetPay.Text.Trim(), txtDesc_NetPay.Text.Trim() );
		model.AliPaySeo = new Seo( txtTitle_AliPay.Text.Trim(), txtKey_AliPay.Text.Trim(), txtDesc_AliPay.Text.Trim() );
		model.KuaiQianSeo = new Seo( txtTitle_KuaiQian.Text.Trim(), txtKey_KuaiQian.Text.Trim(), txtDesc_KuaiQian.Text.Trim() );
		model.TotalPrizeSeo = new Seo( txtTitle_TotalPrize.Text.Trim(), txtKey_TotalPrize.Text.Trim(), txtDesc_TotalPrize.Text.Trim() );
		model.DDZRankSeo = new Seo( txtTitle_DDZRank.Text.Trim(), txtKey_DDZRank.Text.Trim(), txtDesc_DDZRank.Text.Trim() );
		model.NNTotalRankSeo = new Seo( txtTitle_NNTotalRank.Text.Trim(), txtKey_NNTotalRank.Text.Trim(), txtDesc_NNTotalRank.Text.Trim() );
		model.NNRankSeo = new Seo( txtTitle_NNRank.Text.Trim(), txtKey_NNRank.Text.Trim(), txtDesc_NNRank.Text.Trim() );
		model.WalletRankSeo = new Seo( txtTitle_WalletRank.Text.Trim(), txtKey_WalletRank.Text.Trim(), txtDesc_WalletRank.Text.Trim() );
		model.PromoterSeo = new Seo( txtTile_Promoter.Text.Trim(), txtKey_Promoter.Text.Trim(), txtDesc_Promoter.Text.Trim() );
		model.RankDetail = new Seo( txtTitle_RankDetail.Text.Trim(), txtKey_RankDetail.Text.Trim(), txtDesc_RankDetail.Text.Trim() );
        model.PropBuyListSeo = new Seo(txtTitle_PropList.Text.Trim(), txtKey_PropList.Text.Trim(), txtDesc_PropList.Text.Trim());
       
        model.Userpicture = new Seo(txtTitle_UserPicture.Text.Trim(), txtKey_UserPicture.Text.Trim(), txtDesc_UserPicture.Text.Trim());
       
		SeoConfig.Config = model;

		lblMsg.Text = "SEO内容设置成功！" + DateTime.Now;

		/*int iRows = BLL.Config.Update( BLL.Config.ItemName_SeoKey, txtKey.Text );

		iRows += BLL.Config.Update( BLL.Config.ItemName_SeoDesc, txtDesc.Text );

		if( iRows > 0 )
		{
			UiCommon.StringConfig.SetContent( BLL.Config.ItemName_SeoKey, txtKey.Text );
			UiCommon.StringConfig.SetContent( BLL.Config.ItemName_SeoDesc, txtDesc.Text );
			lblMsg.Text = "SEO内容设置成功！" + DateTime.Now;
			new BLL.AdminLog().Add( UiCommon.AdminLoginInfo.UserName, "修改SEO的内容" );
		}
		else
			lblMsg.Text = "SEO内容设置失败！";
		*/
	}

}
