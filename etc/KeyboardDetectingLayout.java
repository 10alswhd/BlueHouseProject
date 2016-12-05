import android.content.Context;
import android.util.AttributeSet;
import android.widget.RelativeLayout;

public class KeyboardDetectingLayout extends RelativeLayout {

    private boolean isSoftKeyboardVisible;

    public KeyboardDetectingLayout(Context context) {
        super(context);
        this.isSoftKeyboardVisible = false;
    }

    public KeyboardDetectingLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.isSoftKeyboardVisible = false;
    }

    public KeyboardDetectingLayout(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        isSoftKeyboardVisible = false;
    }

    public boolean isSoftKeyboardVisible() {
        return isSoftKeyboardVisible;
    }

    /**
     * Overriding allows to detect if soft keyboard is present based on layout height
     * This solution works only for soft keyboard.
     * Hard keyboard does not impact height of the view.
     * Another solution should be applied for hard keyboard!!!
     * @param widthMeasureSpec
     * @param heightMeasureSpec
     */
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        final int proposedheight = MeasureSpec.getSize(heightMeasureSpec);
        final int actualHeight = getHeight();

        if (actualHeight > proposedheight){
            // Keyboard is shown
            isSoftKeyboardVisible = true;

        } else {
            // Keyboard is hidden
            isSoftKeyboardVisible = false;
        }

        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }
}
