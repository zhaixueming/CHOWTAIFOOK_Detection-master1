//出现界面混乱时，使用以下代码替换对应代码。
ui_mainframe.h
        MainFrame->resize(1900, 1030);
        gridLayout->addLayout(titlebar_layout, 0, 0, 30, 1900);
        gridLayout->addLayout(buttonLayout, 30, 0, 110, 500);
		gridLayout->addLayout(numLayout, 140, 0, 110, 500);
		gridLayout->addLayout(infoLayout, 30, 500, 220, 200);
		gridLayout->addLayout(OCRLayout, 250, 0, 165, 500);
		gridLayout->addLayout(resultLayout, 250, 500, 165, 200);
		gridLayout->addLayout(stereoscopiccamLayout, 415, 0, 615, 700);
		gridLayout->addLayout(cam_layout, 30, 700, 1000, 785);
		gridLayout->addLayout(dataLayout, 30, 1485, 500, 415);
		gridLayout->addLayout(log_layout, 530, 1485, 500, 415);
//出现vtk错误时，使用以下代码替换错误代码。
ui_sixviewswidget.h
         vimo::display::ImageView *view1_widget;
         vimo::display::ImageView *view2_widget;
         vimo::display::ImageView *view3_widget;
         vimo::display::ImageView *view4_widget;
         vimo::display::ImageView *view5_widget;
         vimo::display::ImageView *view6_widget;         
        view1_widget = new vimo::display::ImageView(SixViewsWidget);
        view2_widget = new vimo::display::ImageView(SixViewsWidget);
        view3_widget = new vimo::display::ImageView(SixViewsWidget);
        view4_widget = new vimo::display::ImageView(SixViewsWidget);
        view5_widget = new vimo::display::ImageView(SixViewsWidget);
        view6_widget = new vimo::display::ImageView(SixViewsWidget);
      