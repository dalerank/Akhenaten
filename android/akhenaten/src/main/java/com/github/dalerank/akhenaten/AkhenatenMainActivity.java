package com.github.dalerank.akhenaten;

import android.annotation.TargetApi;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;

import org.libsdl.app.SDLActivity;

public class AkhenatenMainActivity extends SDLActivity {
    private static final int GET_FOLDER_RESULT = 500;

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
        startActivityForResult(DirectorySelectionActivity.newIntent(this, again), GET_FOLDER_RESULT);
    }

    protected boolean shouldAskPermissions() {
        return (Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP_MR1);
    }

    @TargetApi(23)
    protected void askPermissions() {
        String[] permissions = {
                "android.permission.READ_EXTERNAL_STORAGE",
                "android.permission.WRITE_EXTERNAL_STORAGE"
        };
        int requestCode = 200;
        requestPermissions(permissions, requestCode);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (shouldAskPermissions()) {
            askPermissions();
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

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == GET_FOLDER_RESULT) {
            if (resultCode == RESULT_OK && data != null && data.getData() != null) {
                getContext().getContentResolver().takePersistableUriPermission(data.getData(),
                                                                         Intent.FLAG_GRANT_READ_URI_PERMISSION
                                                                                | Intent.FLAG_GRANT_WRITE_URI_PERMISSION);
                FileManager.setBaseUri(data.getData());
            } else {
                FileManager.setBaseUri(Uri.EMPTY);
            }
            gotDirectory();
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    public float getScreenDensity() {
        return getResources().getDisplayMetrics().density;
    }

    private native void gotDirectory();
    //private native void releaseAssetManager();
}
