#include "svg.h"

void svg_text(double left,double baseline, string text)
{
    cout<< "<text x='" << left << "' y='" << baseline << "'>"<< text<< "</text>";
}

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}


void svg_end() {
    cout << "</svg>\n";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout<< "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='"<< stroke <<"' fill='"<<fill<<"'/>";
}

double scaling(double IMAGE_HEIGHT,double BIN_HEIGHT,double bin_count){
    if(BIN_HEIGHT*bin_count <= IMAGE_HEIGHT &&BIN_HEIGHT*bin_count>0){
        return BIN_HEIGHT;}
    return IMAGE_HEIGHT/bin_count;
}

void show_histogram_svg(const vector<size_t>& bins,double BIN_HEIGHT,double bin_count,string version, string Window) {
    const auto IMAGE_WIDTH = 800;
    const auto IMAGE_HEIGHT = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
//    const auto BLOCK_WIDTH = 1;
    const auto STROKE = "aqua";
    const auto FILL = "darkblue";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    BIN_HEIGHT = scaling(IMAGE_HEIGHT,BIN_HEIGHT, bin_count);
    double top = 0;
    double maxima=-1;
    for (size_t bin : bins) {
            if(maxima <bin){
                maxima = bin;
            }
    }
    for (size_t bin : bins) {
        const double bin_width = IMAGE_WIDTH *bin/ maxima;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,STROKE,FILL);
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, version);
    top += BIN_HEIGHT;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, Window);
    svg_end();
}
