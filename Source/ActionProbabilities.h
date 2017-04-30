#include "ActionGenerator.h"

using namespace BWAPI;

std::map<std::string, probName> stringToProbName = {
        { "    Idle", probName::Idle }, { "  Attack", probName::Attack },
        { "Move0000", probName::Move0000 }, { "Move0001", probName::Move0001 }, { "Move0010", probName::Move0010 }, { "Move0011", probName::Move0011 },
        { "Move0100", probName::Move0100 }, { "Move0101", probName::Move0101 }, { "Move0110", probName::Move0110 }, { "Move0111", probName::Move0111 },
        { "Move1000", probName::Move1000 }, { "Move1001", probName::Move1001 }, { "Move1010", probName::Move1010 }, { "Move1011", probName::Move1011 },
        { "Move1100", probName::Move1100 }, { "Move1101", probName::Move1101 }, { "Move1110", probName::Move1110 }, { "Move1111", probName::Move1111 }
};

std::map<probName, std::string> porbNameToString = {
        { probName::Idle, "Idle" }, { probName::Attack, "Attack" },
        { probName::Move0000, "Move0000" }, { probName::Move0001, "Move0001" }, { probName::Move0010, "Move0010" }, { probName::Move0011, "Move0011" },
        { probName::Move0100, "Move0100" }, { probName::Move0101, "Move0101" }, { probName::Move0110, "Move0110" }, { probName::Move0111, "Move0111" },
        { probName::Move1000, "Move1000" }, { probName::Move1001, "Move1001" }, { probName::Move1010, "Move1010" }, { probName::Move1011, "Move1011" },
        { probName::Move1100, "Move1100" }, { probName::Move1101, "Move1101" }, { probName::Move1110, "Move1110" }, { probName::Move1111, "Move1111" }
};

std::map<uint8_t, double> priorProb = {
        { probName::Idle, 0.245887296685 },
        { probName::Attack, 0.803967696629 },
        { probName::Move0000, 0.059308694831 },
        { probName::Move0001, 0.164129987659 },
        { probName::Move0010, 0.0736248236953 },
        { probName::Move0011, 0.160191082803 },
        { probName::Move0100, 0.109700280526 },
        { probName::Move0101, 0.160504009164 },
        { probName::Move0110, 0.115416323166 },
        { probName::Move0111, 0.131375579598 },
        { probName::Move1000, 0.0890801506186 },
        { probName::Move1001, 0.325424657534 },
        { probName::Move1010, 0.111328762651 },
        { probName::Move1011, 0.159285714286 },
        { probName::Move1100, 0.219562155934 },
        { probName::Move1101, 0.310594464899 },
        { probName::Move1110, 0.198407960199 },
        { probName::Move1111, 0.234290001876 }
};

std::map<uint8_t, std::map<uint8_t, double> > likelihoodProb = {
        { probName::Idle, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.0 },
                { probName::Move0000, 0.170844789477 },
                { probName::Move0001, 0.192678850612 },
                { probName::Move0010, 0.0996280122918 },
                { probName::Move0011, 0.0393013100437 },
                { probName::Move0100, 0.0455550164429 },
                { probName::Move0101, 0.228853307456 },
                { probName::Move0110, 0.0180063615289 },
                { probName::Move0111, 0.0243139791903 },
                { probName::Move1000, 0.299207504448 },
                { probName::Move1001, 0.327403094506 },
                { probName::Move1010, 0.36799827484 },
                { probName::Move1011, 0.0786026200873 },
                { probName::Move1100, 0.0824303196938 },
                { probName::Move1101, 0.33403417974 },
                { probName::Move1110, 0.0755296781498 },
                { probName::Move1111, 0.0614049274894 }
        } },
        { probName::Attack, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.769707821985 },
                { probName::Move0000, 0.230554221077 },
                { probName::Move0001, 0.183735860593 },
                { probName::Move0010, 0.166790409224 },
                { probName::Move0011, 0.0390007424553 },
                { probName::Move0100, 0.129405598987 },
                { probName::Move0101, 0.350133205223 },
                { probName::Move0110, 0.0750753373804 },
                { probName::Move0111, 0.0446346682972 },
                { probName::Move1000, 0.203170721055 },
                { probName::Move1001, 0.157880945102 },
                { probName::Move1010, 0.427916320915 },
                { probName::Move1011, 0.0680875223828 },
                { probName::Move1100, 0.122592479364 },
                { probName::Move1101, 0.310564702799 },
                { probName::Move1110, 0.184740358999 },
                { probName::Move1111, 0.0783508756606 }
        } },
        { probName::Move0000, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.288747346072 },
                { probName::Move0000, 1.0 },
                { probName::Move0001, 0.167728237792 },
                { probName::Move0010, 0.200636942675 },
                { probName::Move0011, 0.0817409766454 },
                { probName::Move0100, 0.067940552017 },
                { probName::Move0101, 0.267515923567 },
                { probName::Move0110, 0.0498938428875 },
                { probName::Move0111, 0.02016985138 },
                { probName::Move1000, 0.167728237792 },
                { probName::Move1001, 0.0944798301486 },
                { probName::Move1010, 0.376857749469 },
                { probName::Move1011, 0.0859872611465 },
                { probName::Move1100, 0.0477707006369 },
                { probName::Move1101, 0.171974522293 },
                { probName::Move1110, 0.0987261146497 },
                { probName::Move1111, 0.0774946921444 }
        } },
        { probName::Move0001, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.169590643275 },
                { probName::Move0000, 0.27485380117 },
                { probName::Move0001, 1.0 },
                { probName::Move0010, 0.146616541353 },
                { probName::Move0011, 0.0409356725146 },
                { probName::Move0100, 0.0426065162907 },
                { probName::Move0101, 0.103174603175 },
                { probName::Move0110, 0.0258980785297 },
                { probName::Move0111, 0.0108604845447 },
                { probName::Move1000, 0.224310776942 },
                { probName::Move1001, 0.0860484544695 },
                { probName::Move1010, 0.372180451128 },
                { probName::Move1011, 0.0451127819549 },
                { probName::Move1100, 0.0438596491228 },
                { probName::Move1101, 0.0584795321637 },
                { probName::Move1110, 0.0722639933166 },
                { probName::Move1111, 0.0238095238095 }
        } },
        { probName::Move0010, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.4687100894 },
                { probName::Move0000, 0.378033205619 },
                { probName::Move0001, 0.20945083014 },
                { probName::Move0010, 1.0 },
                { probName::Move0011, 0.0536398467433 },
                { probName::Move0100, 0.11877394636 },
                { probName::Move0101, 0.334610472542 },
                { probName::Move0110, 0.0485312899106 },
                { probName::Move0111, 0.0472541507024 },
                { probName::Move1000, 0.102171136654 },
                { probName::Move1001, 0.106002554278 },
                { probName::Move1010, 0.22349936143 },
                { probName::Move1011, 0.0446998722861 },
                { probName::Move1100, 0.0510855683269 },
                { probName::Move1101, 0.178799489144 },
                { probName::Move1110, 0.0446998722861 },
                { probName::Move1111, 0.0383141762452 }
        } },
        { probName::Move0011, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.186878727634 },
                { probName::Move0000, 0.141153081511 },
                { probName::Move0001, 0.155069582505 },
                { probName::Move0010, 0.13717693837 },
                { probName::Move0011, 1.0 },
                { probName::Move0100, 0.0258449304175 },
                { probName::Move0101, 0.109343936382 },
                { probName::Move0110, 0.0278330019881 },
                { probName::Move0111, 0.037773359841 },
                { probName::Move1000, 0.0735586481113 },
                { probName::Move1001, 0.0457256461233 },
                { probName::Move1010, 0.248508946322 },
                { probName::Move1011, 0.0974155069583 },
                { probName::Move1100, 0.0258449304175 },
                { probName::Move1101, 0.0636182902584 },
                { probName::Move1110, 0.037773359841 },
                { probName::Move1111, 0.0298210735586 }
        } },
        { probName::Move0100, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.516823687752 },
                { probName::Move0000, 0.176312247645 },
                { probName::Move0001, 0.102288021534 },
                { probName::Move0010, 0.197846567968 },
                { probName::Move0011, 0.0269179004038 },
                { probName::Move0100, 1.0 },
                { probName::Move0101, 0.189771197847 },
                { probName::Move0110, 0.0753701211306 },
                { probName::Move0111, 0.0296096904441 },
                { probName::Move1000, 0.165545087483 },
                { probName::Move1001, 0.0484522207268 },
                { probName::Move1010, 0.398384925976 },
                { probName::Move1011, 0.0659488559892 },
                { probName::Move1100, 0.0578734858681 },
                { probName::Move1101, 0.117092866756 },
                { probName::Move1110, 0.135935397039 },
                { probName::Move1111, 0.0619111709287 }
        } },
        { probName::Move0101, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.362260919212 },
                { probName::Move0000, 0.271767056808 },
                { probName::Move0001, 0.146731373109 },
                { probName::Move0010, 0.220382529261 },
                { probName::Move0011, 0.0342563516985 },
                { probName::Move0100, 0.069654581787 },
                { probName::Move0101, 1.0 },
                { probName::Move0110, 0.05795032829 },
                { probName::Move0111, 0.0251213245789 },
                { probName::Move1000, 0.216956894091 },
                { probName::Move1001, 0.0636597202398 },
                { probName::Move1010, 0.48073080217 },
                { probName::Move1011, 0.0471024835855 },
                { probName::Move1100, 0.0716528689695 },
                { probName::Move1101, 0.0879246360263 },
                { probName::Move1110, 0.137310876392 },
                { probName::Move1111, 0.0416785612332 }
        } },
        { probName::Move0110, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.688095238095 },
                { probName::Move0000, 0.161904761905 },
                { probName::Move0001, 0.119047619048 },
                { probName::Move0010, 0.138095238095 },
                { probName::Move0011, 0.0261904761905 },
                { probName::Move0100, 0.128571428571 },
                { probName::Move0101, 0.230952380952 },
                { probName::Move0110, 1.0 },
                { probName::Move0111, 0.0285714285714 },
                { probName::Move1000, 0.0380952380952 },
                { probName::Move1001, 0.0428571428571 },
                { probName::Move1010, 0.233333333333 },
                { probName::Move1011, 0.0214285714286 },
                { probName::Move1100, 0.0619047619048 },
                { probName::Move1101, 0.0761904761905 },
                { probName::Move1110, 0.0619047619048 },
                { probName::Move1111, 0.0380952380952 }
        } },
        { probName::Move0111, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.405882352941 },
                { probName::Move0000, 0.141176470588 },
                { probName::Move0001, 0.117647058824 },
                { probName::Move0010, 0.138235294118 },
                { probName::Move0011, 0.117647058824 },
                { probName::Move0100, 0.05 },
                { probName::Move0101, 0.194117647059 },
                { probName::Move0110, 0.0264705882353 },
                { probName::Move0111, 1.0 },
                { probName::Move1000, 0.0823529411765 },
                { probName::Move1001, 0.0411764705882 },
                { probName::Move1010, 0.361764705882 },
                { probName::Move1011, 0.138235294118 },
                { probName::Move1100, 0.0529411764706 },
                { probName::Move1101, 0.0882352941176 },
                { probName::Move1110, 0.138235294118 },
                { probName::Move1111, 0.0647058823529 }
        } },
        { probName::Move1000, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.288043478261 },
                { probName::Move0000, 0.1461352657 },
                { probName::Move0001, 0.117149758454 },
                { probName::Move0010, 0.0730676328502 },
                { probName::Move0011, 0.0175120772947 },
                { probName::Move0100, 0.0960144927536 },
                { probName::Move0101, 0.288043478261 },
                { probName::Move0110, 0.0157004830918 },
                { probName::Move0111, 0.0138888888889 },
                { probName::Move1000, 1.0 },
                { probName::Move1001, 0.1461352657 },
                { probName::Move1010, 0.239130434783 },
                { probName::Move1011, 0.0259661835749 },
                { probName::Move1100, 0.0718599033816 },
                { probName::Move1101, 0.210144927536 },
                { probName::Move1110, 0.0489130434783 },
                { probName::Move1111, 0.0175120772947 }
        } },
        { probName::Move1001, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.157770668463 },
                { probName::Move0000, 0.0843576359657 },
                { probName::Move0001, 0.0996800808217 },
                { probName::Move0010, 0.037548408823 },
                { probName::Move0011, 0.00724027614076 },
                { probName::Move0100, 0.0176797440647 },
                { probName::Move0101, 0.0560700454622 },
                { probName::Move0110, 0.00589324802155 },
                { probName::Move0111, 0.00420946287254 },
                { probName::Move1000, 0.274962114834 },
                { probName::Move1001, 1.0 },
                { probName::Move1010, 0.170904192625 },
                { probName::Move1011, 0.0235729920862 },
                { probName::Move1100, 0.0351911096144 },
                { probName::Move1101, 0.047819498232 },
                { probName::Move1110, 0.0267721838693 },
                { probName::Move1111, 0.0116181175282 }
        } },
        { probName::Move1010, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.521407624633 },
                { probName::Move0000, 0.270381231672 },
                { probName::Move0001, 0.253958944282 },
                { probName::Move0010, 0.132551319648 },
                { probName::Move0011, 0.041935483871 },
                { probName::Move0100, 0.130498533724 },
                { probName::Move0101, 0.43137829912 },
                { probName::Move0110, 0.0492668621701 },
                { probName::Move0111, 0.0375366568915 },
                { probName::Move1000, 0.110850439883 },
                { probName::Move1001, 0.106451612903 },
                { probName::Move1010, 1.0 },
                { probName::Move1011, 0.0648093841642 },
                { probName::Move1100, 0.0653958944282 },
                { probName::Move1101, 0.262170087977 },
                { probName::Move1110, 0.0618768328446 },
                { probName::Move1111, 0.0612903225806 }
        } },
        { probName::Move1011, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.226457399103 },
                { probName::Move0000, 0.0863228699552 },
                { probName::Move0001, 0.122197309417 },
                { probName::Move0010, 0.106502242152 },
                { probName::Move0011, 0.0560538116592 },
                { probName::Move0100, 0.0470852017937 },
                { probName::Move0101, 0.189461883408 },
                { probName::Move0110, 0.0134529147982 },
                { probName::Move0111, 0.0526905829596 },
                { probName::Move1000, 0.0964125560538 },
                { probName::Move1001, 0.113228699552 },
                { probName::Move1010, 0.403587443946 },
                { probName::Move1011, 1.0 },
                { probName::Move1100, 0.02466367713 },
                { probName::Move1101, 0.119955156951 },
                { probName::Move1110, 0.0392376681614 },
                { probName::Move1111, 0.0717488789238 }
        } },
        { probName::Move1100, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.424489795918 },
                { probName::Move0000, 0.174927113703 },
                { probName::Move0001, 0.11195335277 },
                { probName::Move0010, 0.110787172012 },
                { probName::Move0011, 0.0134110787172 },
                { probName::Move0100, 0.0903790087464 },
                { probName::Move0101, 0.258309037901 },
                { probName::Move0110, 0.0373177842566 },
                { probName::Move0111, 0.0227405247813 },
                { probName::Move1000, 0.225072886297 },
                { probName::Move1001, 0.11195335277 },
                { probName::Move1010, 0.322448979592 },
                { probName::Move1011, 0.0396501457726 },
                { probName::Move1100, 1.0 },
                { probName::Move1101, 0.127113702624 },
                { probName::Move1110, 0.0857142857143 },
                { probName::Move1111, 0.0268221574344 }
        } },
        { probName::Move1101, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.26052210975 },
                { probName::Move0000, 0.209376664891 },
                { probName::Move0001, 0.11294619073 },
                { probName::Move0010, 0.138652104422 },
                { probName::Move0011, 0.0247735748535 },
                { probName::Move0100, 0.0475492807672 },
                { probName::Move0101, 0.12799680341 },
                { probName::Move0110, 0.0307671816729 },
                { probName::Move0111, 0.0185135855088 },
                { probName::Move1000, 0.298614810868 },
                { probName::Move1001, 0.0929675013319 },
                { probName::Move1010, 0.436600958977 },
                { probName::Move1011, 0.0510122535962 },
                { probName::Move1100, 0.0620671283964 },
                { probName::Move1101, 1.0 },
                { probName::Move1110, 0.0965636654235 },
                { probName::Move1111, 0.0346297282898 }
        } },
        { probName::Move1110, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.558174523571 },
                { probName::Move0000, 0.226178535607 },
                { probName::Move0001, 0.193079237713 },
                { probName::Move0010, 0.12186559679 },
                { probName::Move0011, 0.0255767301906 },
                { probName::Move0100, 0.149949849549 },
                { probName::Move0101, 0.377131394183 },
                { probName::Move0110, 0.0672016048144 },
                { probName::Move0111, 0.0366098294885 },
                { probName::Move1000, 0.0787362086259 },
                { probName::Move1001, 0.110330992979 },
                { probName::Move1010, 0.316449348044 },
                { probName::Move1011, 0.0501504513541 },
                { probName::Move1100, 0.0707121364092 },
                { probName::Move1101, 0.196589769308 },
                { probName::Move1110, 1.0 },
                { probName::Move1111, 0.0336008024072 }
        } },
        { probName::Move1111, {
                { probName::Idle, 1.0 },
                { probName::Attack, 0.357085668535 },
                { probName::Move0000, 0.163330664532 },
                { probName::Move0001, 0.116092874299 },
                { probName::Move0010, 0.149719775821 },
                { probName::Move0011, 0.0656525220176 },
                { probName::Move0100, 0.0584467574059 },
                { probName::Move0101, 0.267413931145 },
                { probName::Move0110, 0.0536429143315 },
                { probName::Move0111, 0.062449959968 },
                { probName::Move1000, 0.0888710968775 },
                { probName::Move1001, 0.0920736589271 },
                { probName::Move1010, 0.493194555645 },
                { probName::Move1011, 0.154523618895 },
                { probName::Move1100, 0.031224979984 },
                { probName::Move1101, 0.147317854283 },
                { probName::Move1110, 0.0736589271417 },
                { probName::Move1111, 1.0 }
        } }
};
