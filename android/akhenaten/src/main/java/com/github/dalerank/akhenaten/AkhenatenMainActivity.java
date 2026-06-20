package com.github.dalerank.akhenaten;

import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import org.libsdl.app.SDLActivity;

public class AkhenatenMainActivity extends SDLActivity {
    private static final int GET_FOLDER_RESULT = 500;
    private static final String TAG = "AkhenatenMainActivity";
    private static final int STARTUP_LOG_MAX_CHARS = 6000;
    private boolean directorySelectionInProgress = false;
    private boolean shouldLaunchInitialDirectorySelection = false;
    private TextView startupLogView;
    private ScrollView startupLogScroll;
    private Button startupLogToggleButton;
    private boolean startupLogVisible = true;

    @Override
    public void onStop() {
        super.onStop();
        //releaseAssetManager();
        FileManager.clearCache();
    }

    @Override
    protected String[] getLibraries() {
        return new String[]{
                "akhenaten"
        };
    }

    @SuppressWarnings("unused")
    public void showDirectorySelection(boolean again) {
        runOnUiThread(() -> {
            if (directorySelectionInProgress) {
                return;
            }
            try {
                appendStartupLog("Opening folder picker...");
                directorySelectionInProgress = true;
                startActivityForResult(DirectorySelectionActivity.newIntent(this, again), GET_FOLDER_RESULT);
            } catch (Exception e) {
                Log.e(TAG, "Unable to launch directory selection", e);
                appendStartupLog("Folder picker failed: " + e.getClass().getSimpleName());
                directorySelectionInProgress = false;
                FileManager.setBaseUri(this, Uri.EMPTY);
                gotDirectory();
            }
        });
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        installStartupLogOverlay();
        clearStartupLog();
        appendStartupLog("App started");
        FileManager.restoreBaseUri(this);
        if (FileManager.hasBaseUri()) {
            appendStartupLog("Remembered folder: " + FileManager.getDisplayName(this));
        } else {
            appendStartupLog("No remembered folder");
        }
        shouldLaunchInitialDirectorySelection = true;
    }

    @Override
    protected void onPostResume() {
        super.onPostResume();
        if (shouldLaunchInitialDirectorySelection && !directorySelectionInProgress) {
            shouldLaunchInitialDirectorySelection = false;
            showDirectorySelection(false);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        // Override to safely handle permission results when SDL2 is statically linked.
        // If SDL2's nativePermissionResult is available, it will be called by the parent.
        // If not, we catch the exception to prevent crashes.
        try {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        } catch (UnsatisfiedLinkError e) {
            // SDL2's nativePermissionResult might not be available when statically linked.
            // This is okay - we can continue without it.
            android.util.Log.d("AkhenatenMainActivity", "SDL2 nativePermissionResult not available (expected when statically linked): " + e.getMessage());
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == GET_FOLDER_RESULT) {
            directorySelectionInProgress = false;
            if (resultCode == RESULT_OK && data != null && data.getData() != null) {
                try {
                    getContext().getContentResolver().takePersistableUriPermission(data.getData(),
                            Intent.FLAG_GRANT_READ_URI_PERMISSION | Intent.FLAG_GRANT_WRITE_URI_PERMISSION);
                } catch (SecurityException e) {
                    Log.w(TAG, "Persistable URI permission was not granted", e);
                    appendStartupLog("Persisted permission warning");
                }
                FileManager.setBaseUri(this, data.getData());
                appendStartupLog("Folder selected: " + FileManager.getDisplayName(this));
            } else {
                FileManager.setBaseUri(this, Uri.EMPTY);
                appendStartupLog("Folder selection cancelled");
            }
            gotDirectory();
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    public float getScreenDensity() {
        return getResources().getDisplayMetrics().density;
    }

    @SuppressWarnings("unused")
    public void clearStartupLog() {
        runOnUiThread(() -> {
            if (startupLogView != null) {
                startupLogView.setText("");
            }
            updateStartupLogVisibility();
        });
    }

    @SuppressWarnings("unused")
    public void appendStartupLog(String message) {
        runOnUiThread(() -> {
            if (startupLogView == null) {
                return;
            }

            CharSequence existing = startupLogView.getText();
            String next = (existing == null || existing.length() == 0)
                    ? message
                    : existing + "\n" + message;
            if (next.length() > STARTUP_LOG_MAX_CHARS) {
                next = next.substring(next.length() - STARTUP_LOG_MAX_CHARS);
            }
            startupLogView.setText(next);
            if (startupLogScroll != null && startupLogVisible) {
                startupLogScroll.post(() -> startupLogScroll.fullScroll(ScrollView.FOCUS_DOWN));
            }
        });
    }

    @SuppressWarnings("unused")
    public void setStartupLogVisible(boolean visible) {
        startupLogVisible = visible;
        runOnUiThread(this::updateStartupLogVisibility);
    }

    private void updateStartupLogVisibility() {
        if (startupLogScroll != null) {
            startupLogScroll.setVisibility(startupLogVisible ? ScrollView.VISIBLE : ScrollView.GONE);
        }
        if (startupLogToggleButton != null) {
            startupLogToggleButton.setText(startupLogVisible ? "Hide log" : "Log");
        }
    }

    private void installStartupLogOverlay() {
        startupLogView = new TextView(this);
        startupLogView.setTextColor(Color.WHITE);
        startupLogView.setTextSize(TypedValue.COMPLEX_UNIT_SP, 12);
        startupLogView.setPadding(dp(8), dp(8), dp(8), dp(8));
        startupLogView.setShadowLayer(2f, 0f, 0f, Color.BLACK);

        startupLogScroll = new ScrollView(this);
        startupLogScroll.setFillViewport(true);
        startupLogScroll.setBackgroundColor(0xAA000000);
        startupLogScroll.addView(startupLogView, new ScrollView.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT
        ));

        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                dp(180),
                Gravity.TOP
        );
        params.leftMargin = dp(8);
        params.topMargin = dp(8);
        params.rightMargin = dp(8);
        addContentView(startupLogScroll, params);

        startupLogToggleButton = new Button(this);
        startupLogToggleButton.setText("Hide log");
        startupLogToggleButton.setTextSize(TypedValue.COMPLEX_UNIT_SP, 12);
        startupLogToggleButton.setPadding(dp(10), dp(6), dp(10), dp(6));
        startupLogToggleButton.setAlpha(0.9f);
        startupLogToggleButton.setOnClickListener(v -> setStartupLogVisible(!startupLogVisible));

        FrameLayout.LayoutParams buttonParams = new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT,
                Gravity.BOTTOM | Gravity.END
        );
        buttonParams.rightMargin = dp(8);
        buttonParams.bottomMargin = dp(8);
        addContentView(startupLogToggleButton, buttonParams);
    }

    private int dp(int value) {
        return Math.round(value * getResources().getDisplayMetrics().density);
    }

    private native void gotDirectory();
    //private native void releaseAssetManager();
}
