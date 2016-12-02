
	
Stock Function

private function stock():void {

if (stockPriceChange > stock_good_threshold) {
myVid.play(stock_up_clip)
Stock.text = ("Stock is Up"); 
StockTextFormat.color = 0x00CC33; //green
//stock_display.backgroundColor = 0x00CC33; //green background 
}
if (stockPriceChange < stock_bad_threshold) {
myVid.play(stock_down_clip); 
Stock.text = ("Stock is Down");
StockTextFormat.color = 0xFF0033; //red
//stock_display.backgroundColor = 0xFF0033; //white background 
}
if ((stockPriceChange < stock_good_threshold) && (stockPriceChange > stock_bad_threshold)) {
myVid.play(stock_no_change_clip); 
var myBool:Boolean ;
myBool = (stockPriceChange < stock_good_threshold && stockPriceChange > stock_bad_threshold);
trace (stock_good_threshold + " " + stock_bad_threshold);
trace ("stock boolean " + myBool);
Stock.text = ("Stock No Change");
StockTextFormat.color = 0xF5F5F5; //white
//stock_display.backgroundColor = 0xF5F5F5; //white background 
} 
if (display_stock_text == "on") { //only display the stock text if set to on
StockDisplayTextTimer.start(); //start the timer to delay 1 second before displaying stock text
}
} 

private function StockDisplayTextTimerEvent(e:TimerEvent):void { 
stock_display.visible = true;
stock_display.defaultTextFormat = StockTextFormat; //need to reapply this again since we changed the font colors above
if (stockPriceChange > 0) { //the number is postive
stock_display.text = ("+" + String(stockPriceChange)); //displays the stock text; 
StockDisplayTextTimer.reset(); //reset the timer so it can play again 
}

else {
stock_display.text = String(stockPriceChange); //displays the stock text; 
StockDisplayTextTimer.reset(); //reset the timer so it can play again
}
StockDisplayTextTimer5s.start();
}

private function StockDisplayTextTimerEvent5s(e:TimerEvent):void { 
stock_display.visible = false;	//its been 5s so now turn off the text
StockDisplayTextTimer5s.reset(); //start the 5 second timer
} 


private function stockLoaderioErrorHandler(event:IOErrorEvent):void {
trace("Stock Loader Error Trapped ioErrorHandler: " + event);
Stock.text = "Stock Internet call failed, check Internet connection or Yahoo Stock API unavailable";
myVid.play(no_internet_clip);
}


